﻿//############################################################################
//      バージョン番号を自動生成
//          バージョン・アップ手順(タグ付けする)
//              ①ルートCMakeLists.txtのproject(VERSION)を修正
//              ②CMakeコンフィグ実行
//              ③kTheolizerSourcesHashをCommitメッセージに入れて、Commitする。
//              ④kTheolizerVersionでタグ付けする。
//          バージョン・アップしないでCommitする時の手順(タグ付けしない)
//              ①kTheolizerSourcesHashをCommitメッセージに入れて、Commitする。
//
//          kTheolizerSourcesHash : Theolizerドライバ or ライブラリ全体のハッシュ値
//          kTheolizerLibraryHash : Theolizerライブラリ・ヘッダのハッシュ値
//
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

char const kTheolizerVersion[]    ="0.4.0-Temp.";
char const kTheolizerSourcesHash[]="b4ac3d5f7d27f122719242880a772365";
char const kTheolizerLibraryHash[]="e7b4db05be730a7bb697df5338e3a435";
