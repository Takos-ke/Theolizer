//############################################################################
/*!
    @brief      ドキュメント・ファイル－使用方法（個別）
    @ingroup    Documents
    @file       7g.modify_class.h
    @author     Yoshinori Tahara
    @date       2017/03/19 Created
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

/*!
    @page ChangingClass クラスのアップデート／バージョン・アップ方法
ここでは、クラス(classとstruct)を修正した時、古いプログラムが保存したデータを回復するための各種指定方法を説明します。<br>

<br>
//############################################################################
@section HowToModifyClass1 1.バージョン・アップ対応の仕組み概要
//############################################################################

@subsection HowToModifyClass11 1-1.コア・データ構造
バージョン毎にシリアライズ対象のメンバ変数だけを集めたクラス(TheolizerVersion)を定義しています。これは、当該バージョンで持っていたメンバ変数を管理する内部クラスです。管理メンバはターゲットであるユーザ定義クラスの該当メンバ変数への参照として定義されています。<br>

バージョン・アップ後に追加された変数については、最初にそれを追加したバージョン以降のTheolizerVersionに存在します。バージョン・アップ後に削除された変数は、削除したバージョンの１つ前のTheolizerVersionで当該変数と同じ型のインスタンスDを保持し、それ以前のバージョンについてはこのインスタンスDへの参照となります。<br>

以上の仕組みにより、メンバ変数の名前を変更しても、そのアドレスを含めて旧バージョンへ引き継がれますが、型を変更すると引き継ぎできません。その場合は、バージョン・アップ／バージョン・ダウン処理にて変換処理を記述して下さい。ただし、アドレスの引き継ぎはできませんので、オブジェクト追跡は途切れてしまいます。<br>

<div style="padding: 10px; margin-bottom: 10px; border: 1px solid #333333; border-radius: 10px; background-color: #d0d0d0;">
<b>重要事項：</b><br>
Theolizerドライバの主な役割はTheolizerVersionを自動生成することであり、*.theolzier.hppファイルには当該コンパイル単位でシリアライズ指定されているクラスとenum型のTheolizerVersionの定義が生成されます。旧バージョンのTheolizerVersion定義もここに入っていますので、*.theolzier.hppは自動生成ファイルですがバージョン管理システムの管理対象ソースとして登録して下さい。
</div>

@subsection HowToModifyClass12 1-2.侵入型半自動におけるバージョン・アップ／ダウン処理
-  旧バージョンのデータを保存する時の内部動作<br>
ターゲットのユーザ定義クラスから最新版のTheolizerVersionを生成後、次々とカスケードに１つ前のバージョンのTheolizerVersionをコンストラクトする際にメンバ変数を引き継ぎつつ、目的のバージョンのTheolizerVersionまで生成します。そして、そのバージョンのTheolizerVersionを使って保存処理を行います。<br>
この時、<b>１つ前のバージョンのTheolizerVersionを生成後、ユーザ定義のバージョン・ダウン処理（downVersion関数）が定義されていたら、それを呼び出します。</b><br>
<br>

-  旧バージョンのデータから回復する時の内部動作<br>
保存時と同様の流れで、目的のハージョンのTheolizerVersionまで生成します。目的のTheolizerVersionを使って回復処理を行い、生成時と逆の順序でTheolizerVersionをデストラクトしつつ、ターゲットのユーザ定義クラスへ値を戻します。<br>
この時、<b>１つ前バージョンのTheolizerVersionをデストラクトする時に、ユーザ定義のバージョン・アップ処理（upVersion関数）が定義されていたら、それを呼び出します。</b><br>
<br>

@subsection HowToModifyClass13 1-3.非侵入型手動におけるバージョン・アップ／ダウン処理
こちらは半自動型と異なり、カスケードにバージョン・アップ／ダウンを行うことはたいへん難しく、却ってあなたのプログラム開発の手間を増大させるため、カスケード処理は行いません。<br>
各バージョン毎に保存処理と回復処理を記述して下さい。ターゲットのクラスと保存／回復処理間のI/Fに変化がなければ保存／回復処理の変更は不要です。しかし、もし、このI/Fを変更された場合は、それに合わせて全ての保存／回復処理の変更が必要となります。<br>
<br>

@subsection HowToModifyClass14 1-4.バージョン・アップ時の注意事項
クラス分割して複数の保存先（ファイル）へ保存しているシリアライズ・データを旧バージョンから回復する際の各バージョン・アップ処理(upVersion関数)において、他の保存先へ保存しているメンバ変数Aにアクセスする（依存している）場合は、必ずその依存先のデータを先に回復するようにして下さい。<br>

また、もし、その依存されているメンバ変数Aについてバージョン・アップ処理で値を変更している場合は、バージョン・ダウン処理にて逆変換することで旧バージョンでも適切な値になるように処理することが可能です。<br>

依存されているメンバ変数Aについては下記条件を満たすようにすれば、依存しても問題はでません。<br>
  - メンバ変数Aは、下記処理で元に戻る<br>
旧バージョンの値xからバージョン・アップ処理して最新版へ変更後、最新版からバージョン・ダウン処理して値yへ戻した時、「x==y」であること。<br>

  - 逆の遷移時は一致する必要はありませんし、通常は一致できないと思います。<br>
最新版の値Xからバージョン・ダウン処理して旧バージョン版へ変更後、旧バージョン版から最新版へバージョン・アップ処理して値Yになる時、「X==Y」となる必要はありません。<br>

バージョン・アップ時は変数が取りうる値の範囲を広げることが多いため、新しいバージョンには古いバージョンで取り得なかった値を取ることが多いと思います。ですので、一度古いバージョンへ戻した後最新版へ変換した時に元の値へ戻すことができないことは多いと思います。<br>
<br>

@subsection HowToModifyClass15 1-5.Succeedフラグについて
鋭い方はお気づきと思いますが、上記①の事情がある場合、バージョン・ダウンしてバージョン・アップすると値が元に戻らない場合があります。保存先指定にてクラス分割した結果、回復されなかったメンバ変数はそのようなルートを通ってしまいます。<br>
すると、本来変化するべきでないメンバ変数の値が変化してしまうため、問題が発生します。<br>

そこで、Theolizerは下記処理を導入しています。<br>
- 回復したメンバ変数を次バージョンへ引き継ぐことを示すSuceedフラグをメンバ変数毎に設ける。
- バージョン・アップ処理時、そのフラグが立っていないメンバ変数については前バージョンからの値を引き継がず、元の値に戻す。


<br>
//############################################################################
@section HowToModifyClass2 2.バージョン番号を変えないでクラスを修正
//############################################################################

クラスのバージョン番号の更新無しで行う修正は、enum型と異なりTHEOLIZER_ANNOTATE()を用いて指定することは特にありません。通常通りクラス定義を変更するだけです。

バージョン番号を変えない場合に可能なクラスの修正は以下のものがあります。

1. 名前対応の場合
  - メンバ変数の追加<br>
メンバ変数を任意の位置へ追加できます。古いシリアライズ・データを回復する時、新規追加したメンバ変数の値は変更せず、そのまま維持します。ただし、オーナー指定ポインタへ回復する際に領域を獲得した時はコンストラクタにて初期化された値となります。<br>
<br>

  - メンバ変数の削除<br>
任意の位置のメンバ変数を削除できます。古いシリアライズ・データには削除したメンバ変数に対応するデータが含まれていますが、そのデータは破棄されます。<br>
<br>

  - メンバ変数の順序変更<br>
メンバ変数の定義順序の変更が可能です。メンバ変数名で対応付けて正しい変数へ回復します。<br>
<br>

  - 基底クラスについて<br>
基底クラスの追加／削除／順序変更はメンバ変数の変更に準じます。<br>
なお、基底クラスは"(基底クラス名)"と言う名前でシリアライス・データへ記録します。<br>
<br>

2. 順序対応の場合
  - メンバ変数の追加<br>
メンバ変数の並びの最後へのみ追加できます。古いシリアライズ・データを回復する時、新規追加したメンバ変数の値は変更せず、そのまま維持します。ただし、オーナー指定ポインタへ回復する際に領域を獲得した時はコンストラクタにて初期化された値となります。<br>
<br>

  - メンバ変数の削除<br>
メンバ変数の並びの最後からのみ削除できます。（途中を削除することはできません。）古いシリアライズ・データには削除したメンバ変数に対応するデータが含まれていますが、そのデータは破棄されます。<br>
<br>

  - メンバ変数の順序変更<br>
頭から順に回復しますので、定義順序の変更には対応できません。
<br>

  - 基底クラスについて<br>
基底クラスの追加／削除／順序変更はメンバ変数の変更に準じます。<br>
<br>

3. 配列について
  - 考え方<br>
配列は、順序対応に準じた考え方です。<br>
<br>

  - 要素数の増加<br>
要素を増やすと、従来の要素列の最後に追加されます。古いシリアライズ・データを回復する時、新規追加したメンバ変数の値は変更せず、そのまま維持します。<br>
<br>

  - 要素数の減少<br>
要素を減らすと、従来の要素列の際がから削除されます。古いシリアライズ・データには削除したメンバ変数に対応するデータが含まれていますが、そのデータは破棄されます。<br>
<br>

  - 配列の要素数の上限<br>
バージョン番号変更時に要素毎の引き継ぎが必要です。それをコンパイル時に再帰関数を用いて処理していますので、あまり大きな配列に対応できません。<br>
現在、プリビルド版を提供している環境では要素数はtest_modify_class.hのArraySizeTest::kSizeで定義してテストしています。<br>
<br>

4. 違反した場合
例えば、順序対応において変数の並び順を変更した場合、シリアライズ・データ内の変数と異なる変数へデータを回復しようとします。もしも、同じ型の変数であった場合はそのまま回復してしまいます。もしも、異なる型の変数だった場合、２つの事態があります。
  - シリアライザのコンストラクト時にTypeCheckかTypeCheckByIndexを指定した場合<br>
この場合は型チェックを行います。互換性のない型から回復しようとした場合、エラーになります。
  - それ以外の場合<br>
異常動作します。多くの場合はフォーマット・エラーが発生しますが、エラーになることを保証できません。<br>
<br>

<div style="padding: 10px; margin-bottom: 10px; border: 1px solid #333333; border-radius: 10px; background-color: #d0d0d0;">
<b>注意事項：</b><br>
enum型はバージョン・アップ無しでのシンボル名／値変更に対応していましたが、クラスでシンボル名を変更する時はバージョン・アップが必要です。原理的には変更可能ですので要望があれば対応します。
</div>

<br>
//############################################################################
@section HowToMakeGlobalVersionNoTable2 3.グローバル・バージョン番号テーブル生成
//############################################################################

クラスについてもバージョン・アップする際にはグローバル・バージョン番号テーブルが必要です。<br>
enum型の場合と同じですので、詳しくは@ref HowToMakeGlobalVersionNoTable を参照下さい。

<br>
//############################################################################
@section HowToModifyClass4 4.バージョン番号を変えてクラスを修正
//############################################################################

1. 名前対応の場合
  - メンバ変数の追加<br>
<br>

  - メンバ変数の削除<br>
<br>

  - メンバ変数の順序変更<br>
<br>

  - 基底クラスについて<br>
<br>

2. 順序対応の場合
  - メンバ変数の追加<br>
<br>

  - メンバ変数の削除<br>
<br>

  - メンバ変数の順序変更<br>
<br>

  - 基底クラスについて<br>
<br>

3. 配列について
  - 考え方<br>
配列は、順序対応に準じた考え方です。
配列の要素数はバージョン番号変更無しで変更できますが、次元数はバージョン変更時にのみ可能です。ただし、配列単独ではバージョン番号を管理できる仕組みに対応していませんので、クラス・メンバとしての配列のみ次元数変更が可能です。<br>
<br>

  - 要素数の増加<br>
<br>

  - 要素数の減少<br>
<br>


<br>
@subsection HowToModifyClass32 3-2.


*/
