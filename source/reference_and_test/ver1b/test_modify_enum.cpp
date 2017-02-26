﻿//############################################################################
//      Theolizer仕様／テスト・プログラム
//
//          enum型変更の使い方
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

#include "disable_test.h"
#ifndef DISABLE_MODIFY_ENUM_TEST

// ***************************************************************************
//      インクルード
// ***************************************************************************

// 標準ライブラリ
#include <iostream>
#include <fstream>
#include <string>

// theolizerライブラリ
#include <theolizer/serializer_binary.h>
#include <theolizer/serializer_json.h>

// プロジェクト・ヘッダ
#include "common.h"
#include "test_modify_enum.h"

// 自動生成ソース
#include "test_modify_enum.cpp.theolizer.hpp"

//############################################################################
//      
//############################################################################

// ***************************************************************************
//      保存
// ***************************************************************************

//! [saveModifyEnum]
template<class tSerializer>
void saveModifyEnum(tSerializer& iSerializer)
{

//      ---<<< enum型(完全自動型) >>>---

    {
        EnumFullAuto    aEnumFullAuto0(eefaValue1);
        EnumFullAuto    aEnumFullAuto1(eefaName10);
        EnumFullAuto    aEnumFullAuto2(eefaName20);
        EnumFullAuto    aEnumFullAuto3(eefaName41);
        EnumFullAuto    aEnumFullAuto4(eefaName42);
        EnumFullAuto    aEnumFullAuto5(eefaName30);
        EnumFullAuto    aEnumFullAuto6(eefaName51);
        EnumFullAuto    aEnumFullAuto7(eefaName52);
        EnumFullAuto    aEnumFullAuto8(eefaDeleted);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto0);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto1);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto2);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto3);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto4);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto5);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto6);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto7);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto8);

        ScopedEnumFullAuto  aScopedEnumFullAuto0(ScopedEnumFullAuto::Value1);
        ScopedEnumFullAuto  aScopedEnumFullAuto1(ScopedEnumFullAuto::Name10);
        ScopedEnumFullAuto  aScopedEnumFullAuto2(ScopedEnumFullAuto::Name20);
        ScopedEnumFullAuto  aScopedEnumFullAuto3(ScopedEnumFullAuto::Name41);
        ScopedEnumFullAuto  aScopedEnumFullAuto4(ScopedEnumFullAuto::Name42);
        ScopedEnumFullAuto  aScopedEnumFullAuto5(ScopedEnumFullAuto::Name30);
        ScopedEnumFullAuto  aScopedEnumFullAuto6(ScopedEnumFullAuto::Name51);
        ScopedEnumFullAuto  aScopedEnumFullAuto7(ScopedEnumFullAuto::Name52);
        ScopedEnumFullAuto  aScopedEnumFullAuto8(ScopedEnumFullAuto::Deleted);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto0);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto1);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto2);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto3);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto4);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto5);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto6);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto7);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto8);
    }

//      ---<<< enum型(半自動型－シンボル名対応) >>>---

    {
        EnumSymName aEnumSymName0(eesnValue1);
        EnumSymName aEnumSymName1(eesnName10);
        EnumSymName aEnumSymName2(eesnName20);
        EnumSymName aEnumSymName3(eesnName41);
        EnumSymName aEnumSymName4(eesnName42);
        EnumSymName aEnumSymName5(eesnName30);
        EnumSymName aEnumSymName6(eesnName51);
        EnumSymName aEnumSymName7(eesnName52);
        EnumSymName aEnumSymName8(eesnDeleted);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName0);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName1);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName2);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName3);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName4);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName5);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName6);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName7);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName8);

        ScopedEnumSymName   aScopedEnumSymName0(ScopedEnumSymName::Value1);
        ScopedEnumSymName   aScopedEnumSymName1(ScopedEnumSymName::Name10);
        ScopedEnumSymName   aScopedEnumSymName2(ScopedEnumSymName::Name20);
        ScopedEnumSymName   aScopedEnumSymName3(ScopedEnumSymName::Name41);
        ScopedEnumSymName   aScopedEnumSymName4(ScopedEnumSymName::Name42);
        ScopedEnumSymName   aScopedEnumSymName5(ScopedEnumSymName::Name30);
        ScopedEnumSymName   aScopedEnumSymName6(ScopedEnumSymName::Name51);
        ScopedEnumSymName   aScopedEnumSymName7(ScopedEnumSymName::Name52);
        ScopedEnumSymName   aScopedEnumSymName8(ScopedEnumSymName::Deleted);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName0);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName1);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName2);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName3);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName4);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName5);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName6);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName7);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName8);
    }

//      ---<<< enum型(半自動型－シンボル値対応) >>>---

    {
        EnumSymVal  aEnumSymVal0(eesvName10);
        EnumSymVal  aEnumSymVal1(eesvValue10);
        EnumSymVal  aEnumSymVal2(eesvValue20);
        EnumSymVal  aEnumSymVal3(eesvValue41);
        EnumSymVal  aEnumSymVal4(eesvValue42);
        EnumSymVal  aEnumSymVal5(eesvValue30);
        EnumSymVal  aEnumSymVal6(eesvValue51);
        EnumSymVal  aEnumSymVal7(eesvValue52);
        EnumSymVal  aEnumSymVal8(eesvDeleted);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal0);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal1);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal2);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal3);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal4);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal5);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal6);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal7);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal8);

        ScopedEnumSymVal    aScopedEnumSymVal0(ScopedEnumSymVal::Name10);
        ScopedEnumSymVal    aScopedEnumSymVal1(ScopedEnumSymVal::Value10);
        ScopedEnumSymVal    aScopedEnumSymVal2(ScopedEnumSymVal::Value20);
        ScopedEnumSymVal    aScopedEnumSymVal3(ScopedEnumSymVal::Value41);
        ScopedEnumSymVal    aScopedEnumSymVal4(ScopedEnumSymVal::Value42);
        ScopedEnumSymVal    aScopedEnumSymVal5(ScopedEnumSymVal::Value30);
        ScopedEnumSymVal    aScopedEnumSymVal6(ScopedEnumSymVal::Value51);
        ScopedEnumSymVal    aScopedEnumSymVal7(ScopedEnumSymVal::Value52);
        ScopedEnumSymVal    aScopedEnumSymVal8(ScopedEnumSymVal::Deleted);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal0);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal1);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal2);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal3);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal4);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal5);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal6);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal7);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal8);
    }
}
//! [saveModifyEnum]

INSTANTIATION_ALL(saveModifyEnum);

// ***************************************************************************
//      回復
// ***************************************************************************

//! [loadModifyEnum]
template<class tSerializer>
void loadModifyEnum(tSerializer& iSerializer)
{
//theolizer::DisplayPass aDisplayPass;

    std::size_t aIndex=gIndex;
    if (aIndex == kDefaultIndex)
    {
        aIndex=gProgramIndex;
    }

    VersionEnum aVersionEnum=gVersionList[aIndex].mVersionEnum;
    std::cout << "    loadModifyEnum(" << aVersionEnum << ");\n";

//      ---<<< enum型(完全自動型) >>>---

    {
        EnumFullAuto    aEnumFullAuto0(eefaDefault);
        EnumFullAuto    aEnumFullAuto1(eefaDefault);
        EnumFullAuto    aEnumFullAuto2(eefaDefault);
        EnumFullAuto    aEnumFullAuto3(eefaDefault);
        EnumFullAuto    aEnumFullAuto4(eefaDefault);
        EnumFullAuto    aEnumFullAuto5(eefaDefault);
        EnumFullAuto    aEnumFullAuto6(eefaDefault);
        EnumFullAuto    aEnumFullAuto7(eefaDefault);
        EnumFullAuto    aEnumFullAuto8(eefaDefault);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto0);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto1);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto2);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto3);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto4);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto5);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto6);
        THEOLIZER_PROCESS(iSerializer, aEnumFullAuto7);

        // データのバージョンにより切り替え
        switch(aVersionEnum)
        {
        case VersionEnum::ver1a:    // 変更前のバージョン
            {
                THEOLIZER_EQUAL(aEnumFullAuto0, eefaValue1);
                THEOLIZER_EQUAL(aEnumFullAuto1, eefaName10);
                THEOLIZER_EQUAL(aEnumFullAuto2, eefaName20);
                THEOLIZER_EQUAL(aEnumFullAuto3, eefaName20);
                THEOLIZER_EQUAL(aEnumFullAuto4, eefaName20);
                THEOLIZER_EQUAL(aEnumFullAuto5, eefaName30);
                THEOLIZER_EQUAL(aEnumFullAuto6, eefaName30);
                THEOLIZER_EQUAL(aEnumFullAuto7, eefaName30);

                THEOLIZER_PROCESS(iSerializer, aEnumFullAuto8);
                theolizer::ErrorInfo aErrorInfo=iSerializer.getErrorInfo();
                THEOLIZER_EQUAL(aErrorInfo.getErrorType(), theolizer::ErrorType::Warning,
                    aErrorInfo);
                iSerializer.resetError();
            }
            break;

        case VersionEnum::ver1b:   // 変更後のバージョン
            {
                THEOLIZER_EQUAL(aEnumFullAuto0, eefaValue1);
                THEOLIZER_EQUAL(aEnumFullAuto1, eefaName10);
                THEOLIZER_EQUAL(aEnumFullAuto2, eefaName20);
                THEOLIZER_EQUAL(aEnumFullAuto3, eefaName41);
                THEOLIZER_EQUAL(aEnumFullAuto4, eefaName42);
                THEOLIZER_EQUAL(aEnumFullAuto5, eefaName30);
                THEOLIZER_EQUAL(aEnumFullAuto6, eefaName51);
                THEOLIZER_EQUAL(aEnumFullAuto7, eefaName52);

                THEOLIZER_PROCESS(iSerializer, aEnumFullAuto8);
                THEOLIZER_EQUAL(aEnumFullAuto8, eefaDeleted);
            }
            break;

        default:
            THEOLIZER_INTERNAL_ABORT("Version Index(%1%:%2%) Error", aIndex,
                gVersionList[aIndex].mName);
        }

        ScopedEnumFullAuto  aScopedEnumFullAuto0(ScopedEnumFullAuto::Default);
        ScopedEnumFullAuto  aScopedEnumFullAuto1(ScopedEnumFullAuto::Default);
        ScopedEnumFullAuto  aScopedEnumFullAuto2(ScopedEnumFullAuto::Default);
        ScopedEnumFullAuto  aScopedEnumFullAuto3(ScopedEnumFullAuto::Default);
        ScopedEnumFullAuto  aScopedEnumFullAuto4(ScopedEnumFullAuto::Default);
        ScopedEnumFullAuto  aScopedEnumFullAuto5(ScopedEnumFullAuto::Default);
        ScopedEnumFullAuto  aScopedEnumFullAuto6(ScopedEnumFullAuto::Default);
        ScopedEnumFullAuto  aScopedEnumFullAuto7(ScopedEnumFullAuto::Default);
        ScopedEnumFullAuto  aScopedEnumFullAuto8(ScopedEnumFullAuto::Default);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto0);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto1);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto2);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto3);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto4);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto5);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto6);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto7);

        // データのバージョンにより切り替え
        switch(aVersionEnum)
        {
        case VersionEnum::ver1a:   // 変更前のバージョン
            {
                THEOLIZER_EQUAL(aScopedEnumFullAuto0, ScopedEnumFullAuto::Value1);
                THEOLIZER_EQUAL(aScopedEnumFullAuto1, ScopedEnumFullAuto::Name10);
                THEOLIZER_EQUAL(aScopedEnumFullAuto2, ScopedEnumFullAuto::Name20);
                THEOLIZER_EQUAL(aScopedEnumFullAuto3, ScopedEnumFullAuto::Name20);
                THEOLIZER_EQUAL(aScopedEnumFullAuto4, ScopedEnumFullAuto::Name20);
                THEOLIZER_EQUAL(aScopedEnumFullAuto5, ScopedEnumFullAuto::Name30);
                THEOLIZER_EQUAL(aScopedEnumFullAuto6, ScopedEnumFullAuto::Name30);
                THEOLIZER_EQUAL(aScopedEnumFullAuto7, ScopedEnumFullAuto::Name30);

                THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto8);
                theolizer::ErrorInfo aErrorInfo=iSerializer.getErrorInfo();
                THEOLIZER_EQUAL(aErrorInfo.getErrorType(), theolizer::ErrorType::Warning,
                    aErrorInfo);
                iSerializer.resetError();
            }
            break;

        case VersionEnum::ver1b:   // 変更後のバージョン
            {
                THEOLIZER_EQUAL(aScopedEnumFullAuto0, ScopedEnumFullAuto::Value1);
                THEOLIZER_EQUAL(aScopedEnumFullAuto1, ScopedEnumFullAuto::Name10);
                THEOLIZER_EQUAL(aScopedEnumFullAuto2, ScopedEnumFullAuto::Name20);
                THEOLIZER_EQUAL(aScopedEnumFullAuto3, ScopedEnumFullAuto::Name41);
                THEOLIZER_EQUAL(aScopedEnumFullAuto4, ScopedEnumFullAuto::Name42);
                THEOLIZER_EQUAL(aScopedEnumFullAuto5, ScopedEnumFullAuto::Name30);
                THEOLIZER_EQUAL(aScopedEnumFullAuto6, ScopedEnumFullAuto::Name51);
                THEOLIZER_EQUAL(aScopedEnumFullAuto7, ScopedEnumFullAuto::Name52);

                THEOLIZER_PROCESS(iSerializer, aScopedEnumFullAuto8);
                THEOLIZER_EQUAL(aScopedEnumFullAuto8, ScopedEnumFullAuto::Deleted);
            }
            break;

        default:
            THEOLIZER_INTERNAL_ABORT("Version Index(%1%:%2%) Error", aIndex,
                gVersionList[aIndex].mName);
        }
    }

//      ---<<< enum型(半自動型－シンボル名対応) >>>---

    {
        EnumSymName aEnumSymName0(eesnDefault);
        EnumSymName aEnumSymName1(eesnDefault);
        EnumSymName aEnumSymName2(eesnDefault);
        EnumSymName aEnumSymName3(eesnDefault);
        EnumSymName aEnumSymName4(eesnDefault);
        EnumSymName aEnumSymName5(eesnDefault);
        EnumSymName aEnumSymName6(eesnDefault);
        EnumSymName aEnumSymName7(eesnDefault);
        EnumSymName aEnumSymName8(eesnDefault);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName0);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName1);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName2);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName3);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName4);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName5);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName6);
        THEOLIZER_PROCESS(iSerializer, aEnumSymName7);

        // データのバージョンにより切り替え
        switch(aVersionEnum)
        {
        case VersionEnum::ver1a:   // 変更前のバージョン
            {
                THEOLIZER_EQUAL(aEnumSymName0, eesnValue1);
                THEOLIZER_EQUAL(aEnumSymName1, eesnName10);
                THEOLIZER_EQUAL(aEnumSymName2, eesnName20);
                THEOLIZER_EQUAL(aEnumSymName3, eesnName20);
                THEOLIZER_EQUAL(aEnumSymName4, eesnName20);
                THEOLIZER_EQUAL(aEnumSymName5, eesnName30);
                THEOLIZER_EQUAL(aEnumSymName6, eesnName30);
                THEOLIZER_EQUAL(aEnumSymName7, eesnName30);

                THEOLIZER_PROCESS(iSerializer, aEnumSymName8);
                theolizer::ErrorInfo aErrorInfo=iSerializer.getErrorInfo();
                THEOLIZER_EQUAL(aErrorInfo.getErrorType(), theolizer::ErrorType::Warning,
                    aErrorInfo);
                iSerializer.resetError();
            }
            break;

        case VersionEnum::ver1b:   // 変更後のバージョン
            {
                THEOLIZER_EQUAL(aEnumSymName0, eesnValue1);
                THEOLIZER_EQUAL(aEnumSymName1, eesnName10);
                THEOLIZER_EQUAL(aEnumSymName2, eesnName20);
                THEOLIZER_EQUAL(aEnumSymName3, eesnName41);
                THEOLIZER_EQUAL(aEnumSymName4, eesnName42);
                THEOLIZER_EQUAL(aEnumSymName5, eesnName30);
                THEOLIZER_EQUAL(aEnumSymName6, eesnName51);
                THEOLIZER_EQUAL(aEnumSymName7, eesnName52);

                THEOLIZER_PROCESS(iSerializer, aEnumSymName8);
                THEOLIZER_EQUAL(aEnumSymName8, eesnDeleted);
            }
            break;

        default:
            THEOLIZER_INTERNAL_ABORT("Version Index(%1%:%2%) Error", aIndex,
                gVersionList[aIndex].mName);
        }

        ScopedEnumSymName   aScopedEnumSymName0(ScopedEnumSymName::Default);
        ScopedEnumSymName   aScopedEnumSymName1(ScopedEnumSymName::Default);
        ScopedEnumSymName   aScopedEnumSymName2(ScopedEnumSymName::Default);
        ScopedEnumSymName   aScopedEnumSymName3(ScopedEnumSymName::Default);
        ScopedEnumSymName   aScopedEnumSymName4(ScopedEnumSymName::Default);
        ScopedEnumSymName   aScopedEnumSymName5(ScopedEnumSymName::Default);
        ScopedEnumSymName   aScopedEnumSymName6(ScopedEnumSymName::Default);
        ScopedEnumSymName   aScopedEnumSymName7(ScopedEnumSymName::Default);
        ScopedEnumSymName   aScopedEnumSymName8(ScopedEnumSymName::Default);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName0);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName1);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName2);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName3);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName4);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName5);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName6);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName7);

        // データのバージョンにより切り替え
        switch(aVersionEnum)
        {
        case VersionEnum::ver1a:   // 変更前のバージョン
            {
                THEOLIZER_EQUAL(aScopedEnumSymName0, ScopedEnumSymName::Value1);
                THEOLIZER_EQUAL(aScopedEnumSymName1, ScopedEnumSymName::Name10);
                THEOLIZER_EQUAL(aScopedEnumSymName2, ScopedEnumSymName::Name20);
                THEOLIZER_EQUAL(aScopedEnumSymName3, ScopedEnumSymName::Name20);
                THEOLIZER_EQUAL(aScopedEnumSymName4, ScopedEnumSymName::Name20);
                THEOLIZER_EQUAL(aScopedEnumSymName5, ScopedEnumSymName::Name30);
                THEOLIZER_EQUAL(aScopedEnumSymName6, ScopedEnumSymName::Name30);
                THEOLIZER_EQUAL(aScopedEnumSymName7, ScopedEnumSymName::Name30);

                THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName8);
                theolizer::ErrorInfo aErrorInfo=iSerializer.getErrorInfo();
                THEOLIZER_EQUAL(aErrorInfo.getErrorType(), theolizer::ErrorType::Warning,
                    aErrorInfo);
                iSerializer.resetError();
            }
            break;

        case VersionEnum::ver1b:   // 変更後のバージョン
            {
                THEOLIZER_EQUAL(aScopedEnumSymName0, ScopedEnumSymName::Value1);
                THEOLIZER_EQUAL(aScopedEnumSymName1, ScopedEnumSymName::Name10);
                THEOLIZER_EQUAL(aScopedEnumSymName2, ScopedEnumSymName::Name20);
                THEOLIZER_EQUAL(aScopedEnumSymName3, ScopedEnumSymName::Name41);
                THEOLIZER_EQUAL(aScopedEnumSymName4, ScopedEnumSymName::Name42);
                THEOLIZER_EQUAL(aScopedEnumSymName5, ScopedEnumSymName::Name30);
                THEOLIZER_EQUAL(aScopedEnumSymName6, ScopedEnumSymName::Name51);
                THEOLIZER_EQUAL(aScopedEnumSymName7, ScopedEnumSymName::Name52);

                THEOLIZER_PROCESS(iSerializer, aScopedEnumSymName8);
                THEOLIZER_EQUAL(aScopedEnumSymName8, ScopedEnumSymName::Deleted);
            }
            break;

        default:
            THEOLIZER_INTERNAL_ABORT("Version Index(%1%:%2%) Error", aIndex,
                gVersionList[aIndex].mName);
        }
    }

//      ---<<< enum型(半自動型－シンボル値対応) >>>---

    {
        EnumSymVal  aEnumSymVal0(eesvDefault);
        EnumSymVal  aEnumSymVal1(eesvDefault);
        EnumSymVal  aEnumSymVal2(eesvDefault);
        EnumSymVal  aEnumSymVal3(eesvDefault);
        EnumSymVal  aEnumSymVal4(eesvDefault);
        EnumSymVal  aEnumSymVal5(eesvDefault);
        EnumSymVal  aEnumSymVal6(eesvDefault);
        EnumSymVal  aEnumSymVal7(eesvDefault);
        EnumSymVal  aEnumSymVal8(eesvDefault);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal0);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal1);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal2);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal3);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal4);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal5);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal6);
        THEOLIZER_PROCESS(iSerializer, aEnumSymVal7);

        // データのバージョンにより切り替え
        switch(aVersionEnum)
        {
        case VersionEnum::ver1a:   // 変更前のバージョン
            {
                THEOLIZER_EQUAL(aEnumSymVal0, eesvName10);
                THEOLIZER_EQUAL(aEnumSymVal1, eesvValue10);
                THEOLIZER_EQUAL(aEnumSymVal2, eesvValue20);
                THEOLIZER_EQUAL(aEnumSymVal3, eesvValue20);
                THEOLIZER_EQUAL(aEnumSymVal4, eesvValue20);
                THEOLIZER_EQUAL(aEnumSymVal5, eesvValue30);
                THEOLIZER_EQUAL(aEnumSymVal6, eesvValue30);
                THEOLIZER_EQUAL(aEnumSymVal7, eesvValue30);

                THEOLIZER_PROCESS(iSerializer, aEnumSymVal8);
                theolizer::ErrorInfo aErrorInfo=iSerializer.getErrorInfo();
                THEOLIZER_EQUAL(aErrorInfo.getErrorType(), theolizer::ErrorType::Warning,
                    aErrorInfo);
                iSerializer.resetError();
            }
            break;

        case VersionEnum::ver1b:   // 変更後のバージョン
            {
                THEOLIZER_EQUAL(aEnumSymVal0, eesvName10);
                THEOLIZER_EQUAL(aEnumSymVal1, eesvValue10);
                THEOLIZER_EQUAL(aEnumSymVal2, eesvValue20);
                THEOLIZER_EQUAL(aEnumSymVal3, eesvValue41);
                THEOLIZER_EQUAL(aEnumSymVal4, eesvValue42);
                THEOLIZER_EQUAL(aEnumSymVal5, eesvValue30);
                THEOLIZER_EQUAL(aEnumSymVal6, eesvValue51);
                THEOLIZER_EQUAL(aEnumSymVal7, eesvValue52);

                THEOLIZER_PROCESS(iSerializer, aEnumSymVal8);
                THEOLIZER_EQUAL(aEnumSymVal8, eesvDeleted);
            }
            break;

        default:
            THEOLIZER_INTERNAL_ABORT("Version Index(%1%:%2%) Error", aIndex,
                gVersionList[aIndex].mName);
        }

        ScopedEnumSymVal    aScopedEnumSymVal0(ScopedEnumSymVal::Default);
        ScopedEnumSymVal    aScopedEnumSymVal1(ScopedEnumSymVal::Default);
        ScopedEnumSymVal    aScopedEnumSymVal2(ScopedEnumSymVal::Default);
        ScopedEnumSymVal    aScopedEnumSymVal3(ScopedEnumSymVal::Default);
        ScopedEnumSymVal    aScopedEnumSymVal4(ScopedEnumSymVal::Default);
        ScopedEnumSymVal    aScopedEnumSymVal5(ScopedEnumSymVal::Default);
        ScopedEnumSymVal    aScopedEnumSymVal6(ScopedEnumSymVal::Default);
        ScopedEnumSymVal    aScopedEnumSymVal7(ScopedEnumSymVal::Default);
        ScopedEnumSymVal    aScopedEnumSymVal8(ScopedEnumSymVal::Default);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal0);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal1);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal2);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal3);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal4);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal5);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal6);
        THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal7);

        // データのバージョンにより切り替え
        switch(aVersionEnum)
        {
        case VersionEnum::ver1a:   // 変更前のバージョン
            {
                THEOLIZER_EQUAL(aScopedEnumSymVal0, ScopedEnumSymVal::Name10);
                THEOLIZER_EQUAL(aScopedEnumSymVal1, ScopedEnumSymVal::Value10);
                THEOLIZER_EQUAL(aScopedEnumSymVal2, ScopedEnumSymVal::Value20);
                THEOLIZER_EQUAL(aScopedEnumSymVal3, ScopedEnumSymVal::Value20);
                THEOLIZER_EQUAL(aScopedEnumSymVal4, ScopedEnumSymVal::Value20);
                THEOLIZER_EQUAL(aScopedEnumSymVal5, ScopedEnumSymVal::Value30);
                THEOLIZER_EQUAL(aScopedEnumSymVal6, ScopedEnumSymVal::Value30);
                THEOLIZER_EQUAL(aScopedEnumSymVal7, ScopedEnumSymVal::Value30);

                THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal8);
                theolizer::ErrorInfo aErrorInfo=iSerializer.getErrorInfo();
                THEOLIZER_EQUAL(aErrorInfo.getErrorType(), theolizer::ErrorType::Warning,
                    aErrorInfo);
                iSerializer.resetError();
            }
            break;

        case VersionEnum::ver1b:   // 変更後のバージョン
            {
                THEOLIZER_EQUAL(aScopedEnumSymVal0, ScopedEnumSymVal::Name10);
                THEOLIZER_EQUAL(aScopedEnumSymVal1, ScopedEnumSymVal::Value10);
                THEOLIZER_EQUAL(aScopedEnumSymVal2, ScopedEnumSymVal::Value20);
                THEOLIZER_EQUAL(aScopedEnumSymVal3, ScopedEnumSymVal::Value41);
                THEOLIZER_EQUAL(aScopedEnumSymVal4, ScopedEnumSymVal::Value42);
                THEOLIZER_EQUAL(aScopedEnumSymVal5, ScopedEnumSymVal::Value30);
                THEOLIZER_EQUAL(aScopedEnumSymVal6, ScopedEnumSymVal::Value51);
                THEOLIZER_EQUAL(aScopedEnumSymVal7, ScopedEnumSymVal::Value52);

                THEOLIZER_PROCESS(iSerializer, aScopedEnumSymVal8);
                THEOLIZER_EQUAL(aScopedEnumSymVal8, ScopedEnumSymVal::Deleted);
            }
            break;

        default:
            THEOLIZER_INTERNAL_ABORT("Version Index(%1%:%2%) Error", aIndex,
                gVersionList[aIndex].mName);
        }
    }
}
//! [loadModifyEnum]

INSTANTIATION_ALL(loadModifyEnum);

#endif  // DISABLE_MODIFY_ENUM_TEST
