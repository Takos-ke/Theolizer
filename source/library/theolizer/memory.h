﻿//############################################################################
//      スマート・ポインタ群のシリアライズ
//
//      対応済のスマート・ポインタ
//          std::unique_ptr<>
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

#if !defined(THEOLIZER_INTERNAL_UNIQUE_PTR_H)
#define THEOLIZER_INTERNAL_UNIQUE_PTR_H

#ifndef THEOLIZER_INTERNAL_DOXYGEN

//############################################################################
//      Begin
//############################################################################

#include <memory>
#include <map>
#include "serializer.h"

THEOLIZER_PROVIDED_BY("Theoride Technology");

//############################################################################
//      std::unique_ptr<>
//############################################################################

// ***************************************************************************
//      シリアライズ指定
// ***************************************************************************

THEOLIZER_NON_INTRUSIVE_TEMPLATE_ORDER((template<class T>),
                                        (std::unique_ptr<T>), 1,
                                        unique_ptrPrimary);

//----------------------------------------------------------------------------
//      ユーザ定義
//          回復処理の注意事項：
//              余分なデータの破棄、および、ClassType終了処理のため、
//              必ずiSerializer.readPreElement()がfalseを返却するまで
//              処理しておくこと。
//----------------------------------------------------------------------------

//      ---<<< Version.1 >>>---

template<class T>
template<class tMidSerializer, class tTheolizerVersion>
struct TheolizerNonIntrusive<std::unique_ptr<T>>::
    TheolizerUserDefine<tMidSerializer, tTheolizerVersion, 1>
{
    // 保存
    static void saveClassManual
    (
        tMidSerializer& iSerializer,
        typename tTheolizerVersion::TheolizerTarget const*const& iInstance
    )
    {
        THEOLIZER_PROCESS_OWNER(iSerializer, iInstance->get());
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

        typedef typename tTheolizerVersion::TheolizerTarget TheolizerTarget;
        typedef typename TheolizerTarget::element_type Type;
        Type *aInstance=nullptr;
        THEOLIZER_PROCESS_OWNER(iSerializer, aInstance);
        oInstance->reset(aInstance);
    }
};

//----------------------------------------------------------------------------
//      自動生成
//----------------------------------------------------------------------------

#ifdef  THEOLIZER_WRITE_CODE // ###### std::unique_ptr<T> ######

#define THEOLIZER_GENERATED_LAST_VERSION_NO THEOLIZER_INTERNAL_DEFINE(kLastVersionNo,1)
#define THEOLIZER_GENERATED_CLASS_TYPE std::unique_ptr<T>
#define THEOLIZER_GENERATED_PARAMETER_LIST template<class T>
#define THEOLIZER_GENERATED_UNIQUE_NAME unique_ptrPrimary

//      ---<<< Version.1 >>>---

#define THEOLIZER_GENERATED_VERSION_NO THEOLIZER_INTERNAL_DEFINE(kVersionNo,1)
#define THEOLIZER_GENERATED_CLASS_NAME()\
    THEOLIZER_INTERNAL_TEMPLATE_NAME((u8"std::unique_ptr",T))
#include <theolizer/internal/version_manual.inc>
#undef  THEOLIZER_GENERATED_VERSION_NO

#endif//THEOLIZER_WRITE_CODE // ###### std::unique_ptr<T> ######

//############################################################################
//      std::shared_ptr<>
//############################################################################

// ***************************************************************************
//      シリアライズ指定
// ***************************************************************************

THEOLIZER_NON_INTRUSIVE_TEMPLATE_ORDER((template<class T>),
                                        (std::shared_ptr<T>), 1,
                                        shared_ptrPrimary);

//----------------------------------------------------------------------------
//      ユーザ定義
//          回復処理の注意事項：
//              余分なデータの破棄、および、ClassType終了処理のため、
//              必ずiSerializer.readPreElement()がfalseを返却するまで
//              処理しておくこと。
//----------------------------------------------------------------------------

struct shared_ptrPrimary;

//      ---<<< Version.1 >>>---

template<class T>
template<class tMidSerializer, class tTheolizerVersion>
struct TheolizerNonIntrusive<std::shared_ptr<T>>::
    TheolizerUserDefine<tMidSerializer, tTheolizerVersion, 1>
{
    // 保存
    static void saveClassManual
    (
        tMidSerializer& iSerializer,
        typename tTheolizerVersion::TheolizerTarget const*const& iInstance
    )
    {
        THEOLIZER_PROCESS_OWNER(iSerializer, iInstance->get());
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

        typedef typename tTheolizerVersion::TheolizerTarget TheolizerTarget;
        typedef typename TheolizerTarget::element_type Type;
        Type *aInstance=nullptr;
        THEOLIZER_PROCESS_OWNER(iSerializer, aInstance);

        // nullptrなら追跡しない
        if (!aInstance)
        {
            oInstance->reset();
    return;
        }

        // 既に共有されているならそれを用いる
        // 登録リスト獲得
        typedef std::map<void const*, std::shared_ptr<void const> > SharedPtrMap;
        SharedPtrMap& aSharedPtrMap=
            iSerializer.template getSharedPtrTable<SharedPtrMap>(typeid(shared_ptrPrimary));

        // 派生クラスのインタンスへのポインタ獲得
        void const* aDerivedPointer=theolizer::internal::getDerivedPointer(aInstance);

        // 既に回復したことのあるポインタ
        auto aFound=aSharedPtrMap.find(aDerivedPointer);
        if (aFound != aSharedPtrMap.end())
        {
            *oInstance=std::shared_ptr<Type>(aFound->second, aInstance);
        }

        // 初めて
        else
        {
            oInstance->reset(aInstance);
            std::shared_ptr<void const> temp(*oInstance, aDerivedPointer);
            aSharedPtrMap.insert(aFound, std::make_pair(aDerivedPointer, temp));
        }
    }
};

//----------------------------------------------------------------------------
//      自動生成
//----------------------------------------------------------------------------

#ifdef  THEOLIZER_WRITE_CODE // ###### std::shared_ptr<T> ######

#define THEOLIZER_GENERATED_LAST_VERSION_NO THEOLIZER_INTERNAL_DEFINE(kLastVersionNo,1)
#define THEOLIZER_GENERATED_CLASS_TYPE std::shared_ptr<T>
#define THEOLIZER_GENERATED_PARAMETER_LIST template<class T>
#define THEOLIZER_GENERATED_UNIQUE_NAME shared_ptrPrimary

//      ---<<< Version.1 >>>---

#define THEOLIZER_GENERATED_VERSION_NO THEOLIZER_INTERNAL_DEFINE(kVersionNo,1)
#define THEOLIZER_GENERATED_CLASS_NAME()\
    THEOLIZER_INTERNAL_TEMPLATE_NAME((u8"std::shared_ptr",T))
#include <theolizer/internal/version_manual.inc>
#undef  THEOLIZER_GENERATED_VERSION_NO

#endif//THEOLIZER_WRITE_CODE // ###### std::shared_ptr<T> ######

//############################################################################
//      End
//############################################################################

#endif  // THEOLIZER_INTERNAL_DOXYGEN
#endif  // THEOLIZER_INTERNAL_UNIQUE_PTR_H