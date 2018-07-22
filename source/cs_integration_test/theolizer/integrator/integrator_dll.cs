﻿//############################################################################
//      Theolizerライブラリの連携処理クラス(C#側dll用)
/*
    © 2016 Theoride Technology (http://theolizer.com/) All Rights Reserved.
    "Theolizer" is a registered trademark of Theoride Technology.

    "Theolizer" License
        In the case where you are in possession of a valid “Theolizer” License,
        you may use this file in accordance with the terms and conditions of 
        the use license determined by Theoride Technology.

    General Public License Version 3 ("GPLv3")
        You may use this file in accordance with the terms and conditions of 
        GPLv3 published by Free Software Foundation.
        Please confirm the contents of GPLv3 at https://www.gnu.org/licenses/gpl.txt .
        A copy of GPLv3 is also saved in a LICENSE.TXT file.

    商用ライセンス
        あなたが有効なTheolizer商用ライセンスを保持している場合、
        セオライド テクノロジーの定める使用許諾書の条件に従って、
        このファイルを取り扱うことができます。

    General Public License Version 3(以下GPLv3)
        Free Software Foundationが公表するGPLv3の使用条件に従って、
        あなたはこのファイルを取り扱うことができます。
        GPLv3の内容を https://www.gnu.org/licenses/gpl.txt にて確認して下さい。
        またGPLv3のコピーをLICENSE.TXTファイルにおいてます。
*/
//############################################################################

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using theolizer.internal_space;

namespace theolizer
{
    // ***************************************************************************
    //      C++DLL用連携処理統括クラス
    //          DLLの場合、通常１つしかインスタンス不要なのでシングルトンとする
    //          ただし、Dispose可能とする。
    // ***************************************************************************

    sealed class DllIntegrator : internal_space.CoreIntegrator, IDisposable
    {
        //----------------------------------------------------------------------------
        //      コンストラクタ
        //          get()のみマルチスレッド対応
        //----------------------------------------------------------------------------

        private static DllIntegrator sInstance;
        public static DllIntegrator getInstance
            (SerializerType iSerializerType, bool iNotify, uint iGlobalVersionNo)
        {
            if (sInstance == null)
            {
                sInstance = new DllIntegrator(iSerializerType, iNotify, iGlobalVersionNo);
            }
            return sInstance;
        }
        public static void disposeInstance()
        {
            if (sInstance != null)
            {
                sInstance.Dispose();
                sInstance = null;
            }
        }

        [DllImport(Constants.CppDllName)]
        extern static void CppInitialize
        (
            out Streams oStreams,
            IntPtr iCallback,
            SerializerType iSerializerType,
            bool iNotify
        );

        bool mNotify = false;
        bool mDisposed = false;
        GCHandle mCallbackHandle;
        private DllIntegrator(SerializerType iSerializerType, bool iNotify, uint iGlobalVersionNo)
        {
            mNotify = iNotify;

            DelegateNotifySharedObject callback = notifySharedObject;
            mCallbackHandle = GCHandle.Alloc(callback);
            IntPtr ptr = Marshal.GetFunctionPointerForDelegate(callback);
            CppInitialize(out mStreams, ptr, iSerializerType, mNotify);

            mRequestStream = new CppOStream(mStreams.mRequest);
            mResponseStream = new CppIStream(mStreams.mResponse);
            if (mNotify)
            {
                mNotifyStream = new CppIStream(mStreams.mNotify);
            }

            switch (iSerializerType)
            {
            case SerializerType.Binary:
                throw new NotImplementedException();

            case SerializerType.Json:
                mRequestSerializer = new JsonOSerializer(mRequestStream, iGlobalVersionNo);
                mResponseSerializer = new JsonISerializer(mResponseStream);
                if (mNotify)
                {
                    mNotifySerializer = new JsonISerializer(mNotifyStream);
                }
                break;
            }

            // 通知用スレッド起動
            if (mNotify)
            {
                mTerminated = false;
                mUserContext = SynchronizationContext.Current;
                mNotifyThread = new Thread(new ThreadStart(notifyThread));
                mNotifyThread.Start();
            }
        }

        //----------------------------------------------------------------------------
        //      破棄
        //----------------------------------------------------------------------------

        ~DllIntegrator()
        {
            Dispose(false);
        }

        [DllImport(Constants.CppDllName)]
        extern static void CppFinalize();

        protected void Dispose(bool disposing)
        {
            if (mDisposed)
        return;
            mDisposed = true;
            mTerminated = true;

            CppFinalize();

            if (mRequestSerializer  != null)    mRequestSerializer.Dispose();
            if (mResponseSerializer != null)    mResponseSerializer.Dispose();
            mRequestStream.Dispose();
            mResponseStream.Dispose();

            if (mNotify)
            {
                mNotifyThread.Join();

                if (mNotifySerializer   != null)    mNotifySerializer.Dispose();
                mNotifyStream.Dispose();
            }
            mCallbackHandle.Free();
        }

        public override void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        //----------------------------------------------------------------------------
        //      共有オブジェクト管理
        //----------------------------------------------------------------------------

        // 状態通知用コールバック(C++からのコールバック)
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void DelegateNotifySharedObject(int iIndex, bool iUserPresaved);

        // 共有オブジェクトの破棄
        [DllImport(Constants.CppDllName)]
        extern static bool CppDisposeShared(int iIndex);

        protected override void disposeSharedDerived(int iIndex)
        {
            if (mDisposed)
        return;

            if (CppDisposeShared(iIndex) == false)
        throw new InvalidOperationException("Presaved shared object by C++ user program.");
        }

        //----------------------------------------------------------------------------
        //      ストリーム群
        //----------------------------------------------------------------------------

        [StructLayout(LayoutKind.Sequential)]
        struct Streams
        {
            public IntPtr   mRequest;           // C#->Cpp要求用ストリーム
            public IntPtr   mResponse;          // Cpp->C#応答用ストリーム
            public IntPtr   mNotify;            // Cpp->C#通知用ストリーム
        }

        Streams     mStreams = new Streams();

        // 内部ストリーム
        Stream          mRequestStream;
        Stream          mResponseStream;
        Stream          mNotifyStream;

        //----------------------------------------------------------------------------
        //      シリアライザ
        //----------------------------------------------------------------------------

        BaseSerializer   mRequestSerializer;
        BaseSerializer   mResponseSerializer;
        BaseSerializer   mNotifySerializer;

        // 要求を発行し応答を受信
        public override void sendRequest(ITheolizerInternal iFuncObject, ITheolizerInternal oReturnObject)
        {
            if (mDisposed)
        return;

            // 要求送信
            using (var temp = new BaseSerializer.AutoRestoreSaveProcess
                (mRequestSerializer, iFuncObject.getTypeIndex2()))
            {
                iFuncObject.save(mRequestSerializer);
            }
            mRequestSerializer.flush();

            // 応答受信
            TypeIndex aTypeIndex = oReturnObject.getTypeIndex2();
            using (var temp = new BaseSerializer.AutoRestoreLoadProcess
                (mResponseSerializer, ref aTypeIndex))
            {
                oReturnObject.load(mResponseSerializer);
            }
        }

        // 応答シリアライザのグローバル・バージョン番号(デバッグ用)
        public override UInt32 GlobalVersionNo
        {
            get { return mResponseSerializer.getGlobalVersionNo(); }
        }

        //----------------------------------------------------------------------------
        //      通知用スレッド
        //          スレッド内で例外が発生した場合、
        //          インテグレータ生成時にSynchronizationContext.Currentが有効なら、
        //              当該コンテキストにて例外を投げる。
        //          そうでないなら、そのまま再throw
        //----------------------------------------------------------------------------

        Thread mNotifyThread;
        bool mTerminated;
        SynchronizationContext mUserContext;
        void notifyThread()
        {
            if (mDisposed)
        return;

            ThreadIntegrator.Integrator = this;

            try
            {
                while(!mTerminated)
                {
                    TypeIndex aTypeIndex = new TypeIndex();
                    using (var temp = new BaseSerializer.AutoRestoreLoadProcess
                        (mNotifySerializer, ref aTypeIndex))
                    {
                        var aNotifyObject = theolizer_integrator.FuncClassList.get(aTypeIndex.getIndex());
                        aNotifyObject.load(mNotifySerializer);
                        mUserContext.Post(_=>{ ((ICallFunc)aNotifyObject).callFunc(); }, null);
                    }
                }
            }
            catch(CppDisconnected e)
            {
                // 終了していない場合はバグ
                if (!mTerminated)
                {
                    if (mUserContext == null)
        throw;
                    mUserContext.Post(_=>{ throw new Exception("Exception in notifyThread()", e); }, null);
                }
            }
            catch(Exception e)
            {
                if (mUserContext == null)
        throw;
                mUserContext.Post(_=>{ throw new Exception("Exception in notifyThread()", e); }, null);
            }
        }
    }
}
