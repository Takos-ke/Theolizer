//############################################################################
/*!
    @brief      ドキュメント・ファイル－使用方法（個別）
    @ingroup    Documents
    @file       7c.object_tracking.h
    @author     Yoshinori Tahara
    @date       2017/01/06 Created
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
    @page ObjectTracking オブジェクト追跡について
ここでは、オブジェクト追跡について説明します。

<br>
//############################################################################
@section HowToObjectTracking 1.オブジェクト追跡の使い方
//############################################################################

@subsection HowToObjectTracking11 1-1.ポインタをシリアライズする仕組み
Theolizerはboost::serializationと同様にポインタをファイルへ保存し、そのファイルを回復した時、元のポイント構造を回復できる仕組みを実装しています。

下記のようなオブジェクト追跡処理により実現しています。

<b>・ポインタの保存</b><br>
1. オブジェクトIDテーブル<br>
インスタンスを保存する時に、インスタンスの先頭アドレスに対してオブジェクトIDを割り当て、インスタンスの先頭アドレスとオブジェクトIDの対応表を生成します。<br>

2. ポインタを保存<br>
ポインタの指すアドレスに対応するオブジェクトIDをオブジェクトIDテーブルで求め、オブジェクトIDを保存します。

<b>・ポインタの回復</b><br>
1. オブジェクトIDテーブル<br>
インスタンスを回復する時に、オブジェクトIDに対応するインスタンスの先頭アドレスを記録します。

2. ポインタを回復<br>
オブジェクトIDを読み出し、それに対応するインスタンスの先頭アドレスをオブジェクトIDテーブルで求め、インスタンスの先頭アドレスをポインタに設定します。

インスタンスは任意の「型」のインスタンスですが、これが構造体の場合、構造体全体の先頭アドレスと構造体の先頭メンバの先頭アドレスは一致します。（クラスの場合も同様です。）これらを纏めて１つのオブジェクトIDとすると適切に回復できないため、インスタンスの先頭アドレスだけでなく「型」も一緒に記録し、アドレスと型に対してオブジェクトIDを割り当てています。

<br>
@subsection HowToObjectTracking12 1-2.オブジェクト追跡の問題点
ポインタを保存する前に必ずそのポインタが指すインスタンスを保存できれば特に問題はないのですが、そうとは限りません。<br>

ポインタの指すインスタンスが例えばローカル変数で、それがポインタより後でシリアライズ指示される場合です。<br>
そのようなポイント構造を回復するためには、そのローカル変数の保存は最初にポインタをシリアライズ指示された時ではなく、ローカル変数のシリアライズ指示まで遅らせるべきです。そうしないと順序よく回復できないため回復手順が複雑で負荷が高いものになります。<br>

逆に、ポインタが指している領域の所有権を当該ポインタが持っている場合は、最初にポインタをシリアライズ指示された時にインスタンスを保存すればOKです。最初にポインタを回復する際にインスタンス領域を確保して回復すれば適切にポイント構造を回復できますので。<br>

従って、ポインタがポイント先の所有権を持っているかどうかを判定できればこの問題に対処できます。しかし、残念ながら、シリアライズしようとしているポインタが所有権のある領域を指しているのか、そうでない領域を指しているのか判定する仕組みはありません。

そこで、下記２つの選択肢を検討しました。

1. boost::serializationのようにこのようなケースをエラーとする(*1)<br>
この場合ローカル変数のようなインスタンスはそれをポイントするポインタより先に保存する必要が有ります。できれば避けたい制約と思います。

2. ポインタの属性として所有権の有無をプログラマが指定する
保存順序の制約はなく、処理負荷も特に高くはなりません。その代わりプログラマに少し負担がかかります。<br>

さて、インスタンスの所有権を持つか持たないかをポインタの属性とすることは好ましいと思います。C++11のスマート・ポインタは正にそのような概念に基づいています。スマート・ポインタが管理する領域はスマート・ポインタが所有権を持ち、その他のポインタは所有権を持ちません。これによりメモリ・リークのリスクを大きく低減できるわけです。<br>

そこで、インスタンスの所有権の有無をポインタの属性とする仕組みを実装することで、この問題を回避することにしました。<br>

<div style="padding: 10px; margin-bottom: 10px; border: 1px solid #333333; border-radius: 10px; background-color: #d0d0d0;">
(*1)boostの場合<br>
boost::serializationはこのような使い方を許可していません。上記ケースではローカル変数を保存する時にpointer_conflict例外が投げられます。<br>
["Pointer Conflict" Errors in the Boost Serialization Library](http://www.bnikolic.co.uk/blog/cpp-boost-ser-conflict.html)<br>
[Boost serialization with pointers](http://stackoverflow.com/questions/37747596/boost-serialization-with-pointers)
</div>

<br>
@subsection HowToObjectTracking13 1-3.オブジェクト追跡で用いる用語
以上のため、少し用語を定義しました。

1. 静的定義領域<br>
ポインタが所有権を持つことができない領域です。下記があります。
  - グローバル変数
  - ローカル変数
  - 他のクラスのメンバ変数(非ボインタ)
    これは、例えばstruct Foo { int mInt; };のmIntです。ポインタ側からmIntを獲得／解放することができません。

2. 動的生成領域(*2)<br>
newやnew[]で獲得するインスタンスです。

3. ポインタ型<br>
通常のポインタです。これはポイント先のインスタンスの所有権を持ちません。<br>
静的定義領域、動的生成領域の両方をボイントすることができませ。<br>

4. オーナー・ポインタ型<br>
ポイント先のインスタンスの所有権を持っているポインタです。<br>
当然ですが動的生成領域のみポイント可能です。<br>

<div style="padding: 10px; margin-bottom: 10px; border: 1px solid #333333; border-radius: 10px; background-color: #d0d0d0;">
(*2)「静的定義領域」と言う名称<br>
以前、[teratailで良い名前がないか質問](https://teratail.com/questions/20206)してcatsforepawさんの回答を元に決定しました。遠いところからですが、catsforepawさん、その節はありがとうございました。
</div>

<br>
@subsection HowToObjectTracking14 1-4.オブジェクト追跡対象について
静的定義領域は、全てのシリアライズ対象の変数がオブジェクト追跡候補になります。しかし、実際にポインタでポイントされる変数はその内の一部だけですので、全てをオブジェクト追跡するのは無駄が多いです。<br>
そこで、「@ref Basic21 」で示した方法でオブジェクト追跡対象を絞り込んでいます。

<br>
@subsection HowToObjectTracking15 1-5.型の使い方
<b>・ポインタ型のシリアライズ処理は他の型と同じです。</b>

1. メンバ変数の場合は、通常通り保存指定
2. THEOLIZER_PROCESS()マクロ

<b>・オーナー・ポインタ型のシリアライズ処理は通常と異なる指定が必要です。</b>

1. メンバ変数の場合は、THEOLIZER_ANNOTATE(FS:...<...>Owner)
2. THEOLIZER_PROCESS_OWNER()マクロ



サンプル・ソース

対象は、
    静的定義領域
        グローバル変数、ローカル変数、メンバ変数
            ×
        Pointee指定したプリミティブ、Pointee指定しないクラス、Pointee指定したクラス

    動的定義領域
        プリミティブ、クラス

    ポインタ
        上記全てをポイント

    オーナー・ポインタ
        動的定義領域をポイントするが、同じ領域を2つのオーナー・ポインタでポイントする。
        std::unique_ptr<>
        std::shared_ptr<>

<br>
//############################################################################
@section ClearTracking 2.オブジェクト追跡単位について
//############################################################################
「@ref Base22 」に出てきたオブジェクト追跡単位について説明します。

これはオブジェクトIDテーブルの有効期間です。clearTracking()することで

1. オブジェクトIDテーブルにシリアライズされていないインスタンスが登録されていないか確認します
2. オブジェクトIDテーブルをクリアします

前者により、ユーザ・プログラムのバグ検出をサポートします。<br>
後者により、不要なオブジェクト追跡を解除できるのでバフォーマンスを改善できます。<br>

<b>また、解放したインスンタンスを追跡したままにしていると動作不良が発生します。ですので、シリアライズしたデータを解放する前にclearTracking()することを推奨します。</b>

サンプル・ソース
    エラーが発生する様子を記述する。

    注意点として、クラスはポインタ経由で保存されると自動的にオブジェクト追跡する。
    なので、ローカル変数を保存した後、clearTracking()せずにローカル変数を破棄
    した場合、嫌な問題が起きる。

<br>
//############################################################################
@section Polymorphism 3.ポリモーフィズムの使い方
//############################################################################
ポリモーフィックな基底クラスへのポインタをオーナ・ポインタとしてシリアライズすることで、ポリモーフィックに回復されます。つまり、派生クラスのインスタンスを基底クラスへのポインタでポイントして保存して回復した場合、派生クラスのインスタンスとして回復されます。

サンプル・ソース

    ポリモーフィックに保存／回復できていることを示すソース。

@subsection Polymorphism31 3-1.現在の制約事項

現在のTheolizerでは[2点制約](https://github.com/yossi-tahara/Theolizer/issues/13)があります。<br>
1. 抽象クラスな非侵入型手動クラスに対応していません<br>
自動クラス（非侵入型完全自動クラスと侵入型半自動クラス）については抽象クラスでも派生することでシリアライズできますが、手動クラスについて派生してもシリアライズできません。<br>
対応することは可能と思います。開発に時間がかかるため現時点では対応していません。

2. バージョン・アップしても基底クラスを変更できません。<br>
難易度が高く必要性は低いと思いますので、非対応としました。


<br>
//############################################################################
@section TestObjectTracking 4.オブジェクト追跡の網羅的な使用例（自動テスト）の説明
//############################################################################


<br>
//############################################################################
@section TestPolymorphism 5.ポリモーフィズムの網羅的な使用例（自動テスト）の説明
//############################################################################

*/
