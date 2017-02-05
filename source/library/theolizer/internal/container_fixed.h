﻿//############################################################################
//      
/*!
@brief      Theolizerライブラリの標準コンテナ・サポート(固定長用)
@ingroup    TheolizerLib
@file       container_fixed.h
@author     Yoshinori Tahara(Theoride Technology)
@date       2017/02/02 Created
*/
/*
    Copyright (c) 2016 Yohinori Tahara(Theoride Technology) - http://theolizer.com/

    商用ライセンス
        有効なTheolizer商用ライセンスを保持している人は、
        田原良則(Theoride Technology)と締結している商用ライセンス契約の
        使用条件に従って、このファイルを取り扱うことができます。

    General Public License Version 3(以下GPLv3)
        Free Software Foundationが公表するGPLv3の使用条件に従って、
        あなたはこのファイルを取り扱うことができます。
        GPLv3の内容を https://www.gnu.org/licenses/gpl.txt にて確認して下さい。
        GPLv3のコピーをLICENSE.TXTファイルにおいてます。
*/
//############################################################################

#if !defined(THEOLIZER_INTERNAL_CONTAINER_FIXED_H)
#define THEOLIZER_INTERNAL_CONTAINER_FIXED_H

//############################################################################
//      Begin
//############################################################################

// ***************************************************************************
//          DLL用の警告禁止
// ***************************************************************************

#ifdef _MSC_VER
  #pragma warning(push)
//#pragma warning(disable:4100 4251)
#endif

#ifndef THEOLIZER_INTERNAL_DOXYGEN

// ***************************************************************************
//      前準備
// ***************************************************************************

#define THEOLIZER_INTERNAL_FULL_NAME                                        \
    THEOLZIER_INTERNAL_CONTAINER_NAME<THEOLZIER_INTERNAL_CONTAINER_ARGUMENT>

#define THEOLIZER_INTERNAL_FULL_NAME_POINTEE                                \
    THEOLZIER_INTERNAL_CONTAINER_NAME_POINTEE<THEOLZIER_INTERNAL_CONTAINER_ARGUMENT>

//############################################################################
//      標準型
//############################################################################

// ***************************************************************************
//      シリアライズ指定
// ***************************************************************************

THEOLIZER_NON_INTRUSIVE_TEMPLATE_ORDER((THEOLZIER_INTERNAL_CONTAINER_PARAMETER),
                                        (THEOLIZER_INTERNAL_FULL_NAME), 1,
                                        THEOLZIER_INTERNAL_CONTAINER_UNIQUE);

//----------------------------------------------------------------------------
//      ユーザ定義
//          回復処理の注意事項：
//              余分なデータの破棄、および、ClassType終了処理のため、
//              必ずiSerializer.readPreElement()がfalseを返却するまで
//              処理しておくこと。
//----------------------------------------------------------------------------

//      ---<<< Version.1 >>>---

THEOLZIER_INTERNAL_CONTAINER_PARAMETER
template<class tMidSerializer, class tTheolizerVersion>
struct TheolizerNonIntrusive<THEOLIZER_INTERNAL_FULL_NAME>::
    TheolizerUserDefine<tMidSerializer, tTheolizerVersion, 1>
{
    // 保存
    static void saveClassManual
    (
        tMidSerializer& iSerializer,
        typename tTheolizerVersion::TheolizerTarget const*const& iInstance
    )
    {
        THEOLIZER_PROCESS(iSerializer, iInstance->size());
        auto itr=iInstance->begin();
        for (std::size_t i=0; i < iInstance->size(); ++i, ++itr)
        {
            THEOLIZER_PROCESS(iSerializer, *itr);
        }
    }

    // 回復
    static void loadClassManual
    (
        tMidSerializer& iSerializer,
        typename tTheolizerVersion::TheolizerTarget*& oInstance
    )
    {
        // もし、nullptrなら、インスタンス生成
        if (!oInstance)   oInstance=new typename tTheolizerVersion::TheolizerTarget();

        std::size_t aSize;
        THEOLIZER_PROCESS(iSerializer, aSize);

        // 同じサイズのみ許可する
        THEOLIZER_INTERNAL_ASSERT(aSize == oInstance->size(),
            theolizer::print("Can't support changing size(%1% != %2%).",
            aSize, oInstance->size()));

        // 先に領域をvector内部に生成してから、そこへ回復する。
        //  これにより、要素のコピーやムーブが発生しないようにすることで、
        //  「親」へのポインタが壊れないようにしている。
        auto itr=oInstance->begin();
        for (std::size_t i=0; i < aSize; ++i)
        {
            THEOLIZER_PROCESS(iSerializer, *itr++);
        }
    }
};

//############################################################################
//      被ポインタ型
//############################################################################

// ***************************************************************************
//      シリアライズ指定
// ***************************************************************************

THEOLIZER_NON_INTRUSIVE_TEMPLATE_ORDER((THEOLZIER_INTERNAL_CONTAINER_PARAMETER),
                                        (THEOLIZER_INTERNAL_FULL_NAME_POINTEE), 1,
                                        THEOLZIER_INTERNAL_CONTAINER_UNIQUE_POINTEE);

//----------------------------------------------------------------------------
//      ユーザ定義
//          回復処理の注意事項：
//              余分なデータの破棄、および、ClassType終了処理のため、
//              必ずiSerializer.readPreElement()がfalseを返却するまで
//              処理しておくこと。
//----------------------------------------------------------------------------

//      ---<<< Version.1 >>>---

THEOLZIER_INTERNAL_CONTAINER_PARAMETER
template<class tMidSerializer, class tTheolizerVersion>
struct TheolizerNonIntrusive<THEOLIZER_INTERNAL_FULL_NAME_POINTEE>::
    TheolizerUserDefine<tMidSerializer, tTheolizerVersion, 1>
{
    // 保存
    static void saveClassManual
    (
        tMidSerializer& iSerializer,
        typename tTheolizerVersion::TheolizerTarget const*const& iInstance
    )
    {
        THEOLIZER_PROCESS(iSerializer, iInstance->size());
        auto itr=iInstance->begin();
        for (std::size_t i=0; i < iInstance->size(); ++i, ++itr)
        {
            THEOLIZER_PROCESS_POINTEE(iSerializer, *itr);
        }
    }

    // 回復
    static void loadClassManual
    (
        tMidSerializer& iSerializer,
        typename tTheolizerVersion::TheolizerTarget*& oInstance
    )
    {
        // もし、nullptrなら、インスタンス生成
        if (!oInstance)   oInstance=new typename tTheolizerVersion::TheolizerTarget();

        std::size_t aSize;
        THEOLIZER_PROCESS(iSerializer, aSize);

        // 同じサイズのみ許可する
        THEOLIZER_INTERNAL_ASSERT(aSize == oInstance->size(),
            theolizer::print("Can't support changing size(%1% != %2%).",
            aSize, oInstance->size()));

        // 先に領域をvector内部に生成してから、そこへ回復する。
        //  これにより、要素のコピーやムーブが発生しないようにすることで、
        //  「親」へのポインタが壊れないようにしている。
        auto itr=oInstance->begin();
        for (std::size_t i=0; i < aSize; ++i)
        {
            THEOLIZER_PROCESS_POINTEE(iSerializer, *itr++);
        }
    }
};

#endif  // THEOLIZER_INTERNAL_DOXYGEN

//############################################################################
//      End
//############################################################################

// ***************************************************************************
//          警告抑止解除
// ***************************************************************************

#ifdef _MSC_VER
  #pragma warning(pop)
#endif

#endif  // THEOLIZER_INTERNAL_CONTAINER_FIXED_H
