﻿//############################################################################
//      
/*!
@brief      Theolizerライブラリのコア部(型情報リスト)
@ingroup    TheolizerLib
@file       core_assorted.h
@author     Yoshinori Tahara(Theoride Technology)
@date       2016/07/18 Created
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

#if !defined(THEOLIZER_INTERNAL_CORE_ASSORTED_H)
#define THEOLIZER_INTERNAL_CORE_ASSORTED_H

#include <limits>

// ***************************************************************************
//      基本ツールのインクルード
// ***************************************************************************

#include "../report.h"

//############################################################################
//      Begin
//############################################################################

// ***************************************************************************
//          DLL用の警告禁止
// ***************************************************************************

#ifdef _MSC_VER
  #pragma warning(push)
  #pragma warning(disable:4251)
#endif

//############################################################################
//      グローバル名前空間
//############################################################################

// ***************************************************************************
//      THEOLIZER_WRITE_CODE付随処理
//          解析しない指示(THEOLIZER_NO_ANALYZE)がなく、
//          THEOLIZER_WRITE_CODEが未定義なら定義する。
// ***************************************************************************

#if !defined(THEOLIZER_NO_ANALYZE) && !defined(THEOLIZER_WRITE_CODE)
    //! @todo T.B.D.
    #define THEOLIZER_WRITE_CODE
#endif

// ***************************************************************************
//      ソース自動生成制御
//          ドライバにて下記制御を行う
//              環境変数THEOLIZER_DEVELOPER_NAMEが定義されている時、
//              THEOLIZER_PROVIDED_BY()のdVendor(C文字列)と一致したら、
//              THEOLIZER_PROVIDED_BYが展開されたファイル内の自動生成マクロは更新可能
//              そうでない場合に更新を検出したらエラー
// ***************************************************************************

//! @todo T.B.D.
#define THEOLIZER_PROVIDED_BY(dVendor)

//############################################################################
//      theolizer名前空間定義
//############################################################################

//! theolizer名前空間
namespace theolizer{namespace destination{ }}
namespace theolizerD = theolizer::destination;

namespace theolizer
{

//############################################################################
//      ユーティリティ
//############################################################################

namespace internal
{
#ifndef THEOLIZER_INTERNAL_DOXYGEN

// ***************************************************************************
//      異なるコンテナをポリモーフィックに枚挙するためのRange
//          RBForRangeテクニックを応用しているが、
//          RBForRangeを直接は使えないので別途定義した。
// ***************************************************************************

//----------------------------------------------------------------------------
//      範囲ベースforへ渡すリファレンサー(RBForReferencerの特化)
//----------------------------------------------------------------------------

template<class tPolyRangeBase, class tValueType>
class PolyReferencer
{
    tPolyRangeBase& mPolyRange;
public:
    PolyReferencer(tPolyRangeBase& iPolyRange) : mPolyRange(iPolyRange)
    { }

    tValueType& operator*()
    {
        THEOLIZER_INTERNAL_ASSERT(mPolyRange.mHolder.get(), THEOLIZER_INTERNAL_BUG);
        return mPolyRange.mHolder->front();
    }
    tValueType const& operator*() const
    {
        THEOLIZER_INTERNAL_ASSERT(mPolyRange.mHolder.get(), THEOLIZER_INTERNAL_BUG);
        return mPolyRange.mHolder->front();
    }
    void operator++()
    {
        THEOLIZER_INTERNAL_ASSERT(mPolyRange.mHolder.get(), THEOLIZER_INTERNAL_BUG);
        mPolyRange.mHolder->drop_front();
    }
    bool operator!=(PolyReferencer const& iRhs) const
    {
        if (!mPolyRange.mHolder.get())
    return false;
        return !mPolyRange.mHolder->empty();
    }
};

//----------------------------------------------------------------------------
//      枚挙用Range
//----------------------------------------------------------------------------

template<class tValueType>
class PolyRange
{

//      ---<<< 基底クラス >>>---

    struct HolderBase
    {
        virtual tValueType      & front()       = 0;
        virtual tValueType const& front() const = 0;
        virtual void drop_front() = 0;
        virtual bool empty() const = 0;
        virtual std::size_t size() = 0;

        // これがないとmsvc 2015の「反復子のデバッグのサポート」用の
        //  イテレータのデストラクタが呼ばれないため、異常動作する。
        virtual ~HolderBase() { }
    };

//      ---<<< 実クラス >>>---

    template<typename tIterator>
    struct Holder : public HolderBase
    {
        tIterator   mBegin;
        tIterator   mEnd;
        std::size_t mCount;

        Holder(tIterator&& iBegin, tIterator&& iEnd, std::size_t iCount) :
            mBegin(std::forward<tIterator>(iBegin)),
            mEnd  (std::forward<tIterator>(iEnd)),
            mCount(iCount)
        { }
        ~Holder() = default;

        tValueType& front()
        {
            return *mBegin;
        }
        tValueType const& front() const
        {
            return *mBegin;
        }
        void drop_front()
        {
            ++mBegin;
            --mCount;
        }
        bool empty() const
        {
            return mBegin == mEnd;
        }
        std::size_t size()
        {
            return mCount;
        }
    };

//      ---<<< 各種設定 >>>---

    template<class, class> friend class PolyReferencer;
    typedef PolyReferencer<PolyRange, tValueType>   PolyReferencer_t;

//      ---<<< 記録領域 >>>---

    std::unique_ptr<HolderBase> mHolder;

//      ---<<< コンストラクタ >>>---

public:
    PolyRange() { }

    template<typename tIterator>
    PolyRange(tIterator&& iBegin, tIterator&& iEnd, std::size_t iCount) :
        mHolder
        (
            new Holder<tIterator>
            (
                std::forward<tIterator>(iBegin),
                std::forward<tIterator>(iEnd),
                iCount
            )
        )
    { }

    PolyReferencer_t begin() {return PolyReferencer_t(*this);}
    PolyReferencer_t end()   {return PolyReferencer_t(*this);}
    std::size_t size()
    {
        if (!mHolder.get())
    return 0;
        return mHolder->size();
    }
};

// ***************************************************************************
//      生配列の型定義
//          Array<型, 要素数...>にて生配列の型になる
//          下記2つは同じ定義である。
//              theolizer::Array<int, 10, 20>    aIntArray;
//              int                             aIntArray[10][20];
//          このテンプレートで配列の参照を下記のように定義することができる。
//              theolizer::Array<int, 10>&       aInt10;
//              int                             (&aInt)[10];
//          CoveredArray<型, 要素数...>は上記と同じ記憶領域配置だが型が異なる
//          CoveredArray<int, 2, 3>は下記
//              class ArrayImpl // == CoveredArray
//              {
//                  class ArrayImpl
//                  {
//                      class ArrayImpl
//                      {
//                          int mElement;
//                      } mElements[3];
//                  } mElements[2];
//              };
// ***************************************************************************

template<class tType, size_t... tDims>
struct ArrayImpl
{
    typedef tType type;
    typedef tType CoveredElements;

    // オフセットを合わせるため、中身を定義
    CoveredElements mElement;

    // 中身へのアクセス
    CoveredElements& getElement() {return mElement;}
};

template<class tType, size_t tFirst, size_t... tDims>
struct ArrayImpl<tType, tFirst, tDims...>
{
    typedef typename ArrayImpl<tType, tDims...>::type   type[tFirst];
    typedef ArrayImpl<tType, tDims...> CoveredElements[tFirst];

    // オフセットを合わせるため、中身を定義
    CoveredElements mElements;

    // 1次元配列としてアクセス
    CoveredElements& getElements() {return mElements;}
};

template<class tType, size_t... tDims>
using Array = typename ArrayImpl<tType, tDims...>::type;

template<class tType, size_t... tDims>
using CoveredArray = ArrayImpl<tType, tDims...>;

//############################################################################
//      エラー報告サービス群
//############################################################################

// ***************************************************************************
//      エラー・チェック用サーピス群
// ***************************************************************************

THEOLIZER_INTERNAL_DLL void checkDataShort(bool iIsPass, std::string const& iLoc);
THEOLIZER_INTERNAL_DLL void checkExtraData(bool iIsPass, std::string const& iLoc);

//############################################################################
//      保存先指定
//############################################################################

// ***************************************************************************
//      内部処理用アイテム群
// ***************************************************************************

//----------------------------------------------------------------------------
//      ビット列処理クラス
//----------------------------------------------------------------------------

class THEOLIZER_INTERNAL_DLL BitString
{
    static int const            kUnsignedSize=std::numeric_limits<unsigned>::digits;
    static unsigned const       kUnsignedMax =std::numeric_limits<unsigned>::max();
    std::unique_ptr<unsigned[]> mBitList;       // 記録領域
    unsigned                    mDataCount;     // 保持しているunsignedの数

    // 必要なら記録領域追加
    void expandList(unsigned iIndex);
public:
    BitString() : mBitList(), mDataCount(0) { }

    BitString(BitString&& iRhs) noexcept : 
        mBitList(std::move(iRhs.mBitList)),
        mDataCount(iRhs.mDataCount)
    { }

    // 指定bit追加
    void add(unsigned iBitNo);

    // 指定unsigned追加
    void add(unsigned iIndex, unsigned iData);

    // 指定bit判定
    bool isOne(unsigned iBitNo) const;

    // 文字列化
    std::string to_string(unsigned iStart=0, unsigned iEnd=kUnsignedMax) const;

    // unsigned単位のイテレータ(bit単位は必要ないので省略)
    unsigned* begin() const {return &mBitList[0];}
    unsigned* end()   const {return &mBitList[mDataCount];}
};

#endif  // THEOLIZER_INTERNAL_DOXYGEN
}   // namespace internal

// ***************************************************************************
//      保存先シンボル定義用ツール群
// ***************************************************************************

//----------------------------------------------------------------------------
//      ビット番号を定義するscoped enum型
//          通常の整数型で間違って保存先指定されなよう、scoped enumを用いる。
//          整数型を強い型定義するための流用である。
//
//          名前空間:theolizer
//----------------------------------------------------------------------------

//! @todo T.B.D.
enum class Destination : unsigned { };

//----------------------------------------------------------------------------
//      ビット番号管理ツール
//----------------------------------------------------------------------------

#ifndef THEOLIZER_INTERNAL_DOXYGEN
namespace internal
{
namespace
{

//      ---<<< ビット番号自動生成 >>>---

namespace bits
{
enum : unsigned {All=0};
}   // namespace bits

}   // namespace
}   // namespace internal

//----------------------------------------------------------------------------
//      ユーザが使用する保存先シンボルを定義
//          名前空間:theolizerD
//
//          theolizerD::All      全て保存する
//----------------------------------------------------------------------------

namespace destination
{
namespace
{
    Destination const All=static_cast<Destination>(internal::bits::All);
}   // namespace
}   // namespace destination

//----------------------------------------------------------------------------
//      保存先シンボル定義マクロ
//----------------------------------------------------------------------------

#define THEOLIZER_INTERNAL_DESTINATION(dSymbol)                             \
    namespace destination{namespace{                                        \
    Destination const dSymbol=static_cast<Destination>(internal::bits::dSymbol);\
    }} /* namespace destination */                                          \

// ***************************************************************************
//      保存先を保持するクラス
//          名前空間:theolizer
// ***************************************************************************

namespace internal
{

class Destinations
{
    static unsigned const   kAlways = (1u << static_cast<unsigned>(theolizerD::All));
    internal::BitString   mDestinations;
public:

//----------------------------------------------------------------------------
//      コンストラクタ
//----------------------------------------------------------------------------

    Destinations()
    { }

    Destinations(std::initializer_list<Destination> const& iDestinationList)
    {
        add(iDestinationList);
    }

    Destinations(Destinations&& iRhs) noexcept :
        mDestinations(std::move(iRhs.mDestinations))
    { }

//----------------------------------------------------------------------------
//      要素追加
//----------------------------------------------------------------------------

    void add(std::initializer_list<Destination> const& iDestinationList)
    {
        for (auto destination : iDestinationList)
        {
            unsigned aBitNo = static_cast<unsigned>(destination);
            mDestinations.add(aBitNo);
        }
    }

    void add(Destinations const& iRhs)
    {
        for (auto&& aIndexer : getRBForIndexer(iRhs.mDestinations))
        {
            mDestinations.add(static_cast<unsigned>(aIndexer.getIndex()), aIndexer.front());
        }
    }

//----------------------------------------------------------------------------
//      一致判定
//----------------------------------------------------------------------------

    bool isMatch(Destinations const& iRhs) const
    {
        auto aLhs=mDestinations.begin();
        bool aFirst=true;
        for (auto aRhs : iRhs.mDestinations)
        {
            if (aFirst)
            {
                aFirst=false;
                // どちらか一方のAlwayが1ならtrue
                if ((*aLhs & 1) || (aRhs & 1)) {
    return true;
                }
            }

            if (*aLhs & aRhs) {
    return true;
            }
        }
        return false;
    }

//----------------------------------------------------------------------------
//      表示用
//----------------------------------------------------------------------------

    std::string to_string() const
    {
        return mDestinations.to_string(0, 1)+":"+mDestinations.to_string(1);
    }
    friend std::ostream& operator<<(std::ostream& iOStream, Destinations const& iDestinations)
    {
        iOStream << iDestinations.to_string();
        return iOStream;
    }
};

// ***************************************************************************
//      グローバル・バージョン番号管理
//          クラス・バージョンをまとめてグローバル・バージョンとして管理する
//          そのため、クラスのリストとそれぞれのクラス・バージョンが対応する
//          グローバル・バージョン番号を対応付ける。
// ***************************************************************************

//----------------------------------------------------------------------------
//      キーとローカル・バージョン番号リスト・インデックス
//----------------------------------------------------------------------------

struct GlobalVersionKey
{
    std::type_index mTypeIndex;
    std::size_t     mListIndex;
    GlobalVersionKey(std::type_index iTypeIndex, std::size_t iListIndex) :
        mTypeIndex(iTypeIndex), mListIndex(iListIndex)
    { }
};

//----------------------------------------------------------------------------
//      実装用関数宣言
//----------------------------------------------------------------------------

// キー登録
THEOLIZER_INTERNAL_DLL void addGlobalVersionKey
(
    GlobalVersionKey const& iKey,
    std::vector<GlobalVersionKey>& oKeyList
);

// キー検索
THEOLIZER_INTERNAL_DLL bool findGlobalVersionKey
(
    std::vector<GlobalVersionKey> const& iKeyList,
    std::type_index iTypeIndex,
    std::size_t& oListIndex
);

//----------------------------------------------------------------------------
//      テーブルの基底クラス
//----------------------------------------------------------------------------

class GlobalVersionNoTableBase
{
protected:
    GlobalVersionNoTableBase() { }
    ~GlobalVersionNoTableBase() { }
public:
    virtual char const* getTableName() const {return "";}

    virtual unsigned getLocalVersionNo
        (
            unsigned iGlobalVersionNo,
            std::type_index iStdTypeIndex
        ) const = 0;

    virtual unsigned getGlobalVersionNo
        (
            unsigned iLocalVersionNo,
            std::type_index iStdTypeIndex
        ) const = 0;

    // コピー／ムーブ禁止(デストラクタ定義がないとis_trivially_copyableになる)
    GlobalVersionNoTableBase(const GlobalVersionNoTableBase&)  = delete;
    GlobalVersionNoTableBase(      GlobalVersionNoTableBase&&) = delete;
    GlobalVersionNoTableBase& operator=(const GlobalVersionNoTableBase&)  = delete;
    GlobalVersionNoTableBase& operator=(      GlobalVersionNoTableBase&&) = delete;
};

//----------------------------------------------------------------------------
//      テーブル本体
//          シングルトン
//----------------------------------------------------------------------------

template<unsigned uLastGlobalVersionNo>
class GlobalVersionNoTable : public GlobalVersionNoTableBase
{
    static_assert(uLastGlobalVersionNo != 0, "Global VersionNo.0 is illegal.");

//      ---<<< ローカル・バージョン番号のリスト >>>---

    //  1つで1クラス/enum型のローカル・バージョン番号を保持する
    struct LocalVersionNo
    {
        unsigned        mLocalVersionNo[uLastGlobalVersionNo];
    };
    // 登録順でローカル・バージョン番号を保持する
    std::vector<LocalVersionNo>     mLocalVersionNoList;

//      ---<<< std::type_index(キー)とmLocalVersionNoListとの対応表 >>>---

    // type_indexによるキーでソート
    std::vector<GlobalVersionKey>   mKeyList;

//      ---<<< シングルトン >>>---

protected:
    GlobalVersionNoTable() { }
public:
    static GlobalVersionNoTableBase* getInstance()
    {
        static GlobalVersionNoTable instance;
        return &instance;
    }

//      ---<<< 機能群 >>>---

    // クラス登録
    template<typename... tLocalVersionNoList>
    void add(std::type_info const& iTypeInfo, tLocalVersionNoList... iLocalVersionNoList)
    {
        static_assert(sizeof...(tLocalVersionNoList) == uLastGlobalVersionNo,
                      "GlobalVersionNoTable::add() illegal number of parameters.");

        std::size_t aTypeIndex=mLocalVersionNoList.size();
        mLocalVersionNoList.push_back(LocalVersionNo{iLocalVersionNoList...});
        addGlobalVersionKey(GlobalVersionKey(iTypeInfo, aTypeIndex), mKeyList);
    }

    // 指定クラスの指定グローバル・バージョン番号に該当するローカル・バージョン番号返却
    //  未登録クラスは1を返却する(完全自動型なので)
    unsigned getLocalVersionNo(unsigned iGlobalVersionNo, std::type_index iStdTypeIndex) const
    {
        THEOLIZER_INTERNAL_ASSERT(iGlobalVersionNo != 0,
            "GlobalVersionNoTable::getLocalVersionNo() : iGlobalVersionNo is illegal(0).");
        THEOLIZER_INTERNAL_ASSERT(iGlobalVersionNo <= uLastGlobalVersionNo,
            "GlobalVersionNoTable::getLocalVersionNo() : iGlobalVersionNo is too big.");

        std::size_t aListIndex;
        if (!findGlobalVersionKey(mKeyList, iStdTypeIndex, aListIndex))
    return 1;

        unsigned ret = mLocalVersionNoList[aListIndex].mLocalVersionNo[iGlobalVersionNo-1];

        // 無効な値ならエラー(iGlobalVersionNo時にシリアライズされていなかった時該当する)
        if (!ret)
        {
            THEOLIZER_INTERNAL_DATA_ERROR(
                u8"Can not process <%1%> for Global VersionNo.%2%",
                getNameByTypeId(iStdTypeIndex),
                iGlobalVersionNo
            );
        }
        return ret;
    }

    // 指定クラスの指定ローカル・バージョン番号に該当する最大のグローバル・バージョン番号返却
    //  未登録クラスはuLastGlobalVersionNoを返却する
    unsigned getGlobalVersionNo(unsigned iLocalVersionNo, std::type_index iStdTypeIndex) const
    {
        THEOLIZER_INTERNAL_ASSERT(iLocalVersionNo != 0,
            "GlobalVersionNoTable::getGlobalVersionNo() : iLocalVersionNo is illegal(0).");

        std::size_t aListIndex;
        if (!findGlobalVersionKey(mKeyList, iStdTypeIndex, aListIndex))
    return uLastGlobalVersionNo;

        unsigned ret;
        for (ret=uLastGlobalVersionNo; 0 < ret; --ret)
        {
            if (mLocalVersionNoList[aListIndex].mLocalVersionNo[ret-1] == iLocalVersionNo)
            {
    return ret;
            }
        }

        return uLastGlobalVersionNo;
    }
};

//----------------------------------------------------------------------------
//      ユーザ定義のグローバル・バージョン番号テーブルへのポインタを取込む
//          名前空間は、theolizer::internal::匿名::
//----------------------------------------------------------------------------

namespace{
    extern GlobalVersionNoTableBase const*const sGlobalVersionNoTable;
}   // namespace

//----------------------------------------------------------------------------
//      最新版のグローバル・バージョン番号
//          名前空間は、theolizer::匿名::
//----------------------------------------------------------------------------

}   // namespace internal

namespace
{
    extern unsigned const kLastGlobalVersionNo;
}   // namespace

namespace internal
{

//----------------------------------------------------------------------------
//      ソース自動生成用マクロ
//----------------------------------------------------------------------------

#define THEOLIZER_GENERATED_GLOBAL_TABLE()                                  \
    namespace theolizer{namespace internal{namespace{                       \
        GlobalVersionNoTableBase const*const sGlobalVersionNoTable=         \
            GlobalVersionNoTable<1>::getInstance();                         \
    }}  /* namespace internal */                                            \
    namespace{                                                              \
        unsigned const kLastGlobalVersionNo=1;                              \
    }} /* namespace theolizer */

//############################################################################
//      型管理用ユーティリティ
//############################################################################

// ***************************************************************************
//      型管理用プライマリ・テンプレート定義
// ***************************************************************************

}   // namespace internal
#endif  // THEOLIZER_INTERNAL_DOXYGEN

}   // namespace theolizer

//      ---<<<< 非侵入型/enum型プライマリー・テンプレート >>>---

#ifndef THEOLIZER_INTERNAL_DOXYGEN

template<class tClassType>
struct TheolizerNonIntrusive {};

//      ---<<<< 手動型基底クラス用プライマリー・テンプレート >>>---

template<class tClassType>
class TheolizerBase {};

//      ---<<<< トップ・レベル登録時のバージョン伝達エラー回避用 >>>---
//      コーディング規約上、tで始まる名前はテンプレート引数だが、
//      下記理由により例外とする。
//          手動型のTheolizerUserDefine内でシリアライズ／デシリアライズ
//          指示する際、THEOLIZER_PROCESS()等のマクロを用いる。
//          この手動型のシリアライズ／デシリアライズ指定された型を
//          当該手動型クラスのメンバ型として登録するために、テンプレート・
//          パラメータtTheolizerVersionをTHEOLIZER_PROCESS()等のマクロで用いる。
//          それ以外の場所で、THEOLIZER_PROCESS()等のマクロが使われた時に、
//          tTheolizerVersionが未定義エラーにならないようここで定義する。

struct tTheolizerVersion
{
    template<class tTypeFunc>
    static void addElement(tTypeFunc iTypeFunc)
    {
    }
};
#endif  // THEOLIZER_INTERNAL_DOXYGEN

namespace theolizer
{

// ***************************************************************************
/*!
@brief      型チェック・モード
@details    TypeIndexは「型」に割り当てられるインデックス番号。<br>
            ソフトウェアが起動される時に確定する。
*/
//      InMemoryは、FastSerializer専用
//          変更されていないクラス同士でのみ保存／回復可能な負荷が最も軽いモード。
//          回復時の型チェックを一切行わない。
//          ポインタの先がシリアライズされてなかったら、元のアドレスを回復する。
//          (つまり、そのようなポインタはシャロー・コピーとなる。)
// ***************************************************************************

enum class CheckMode
{
    InMemory,                   //   メモリ内動作のみ、かつ、型チェック無し（非公開）
    NoTypeCheck,                //!< 型チェック無し
    TypeCheck,                  //!< 型名による型チェック
    TypeCheckByIndex,           //!< TypeIndexによる型チェック
    MetaMode                    //   メタ処理－型定義情報を保存／回復（非公開）
};

//! @todo T.B.D.
THEOLIZER_INTERNAL_DLL std::ostream& operator<<(std::ostream& iOStream, CheckMode iCheckMode);

namespace internal
{
#ifndef THEOLIZER_INTERNAL_DOXYGEN

// ***************************************************************************
//      不正値
// ***************************************************************************

THEOLIZER_INTERNAL_DLL extern const std::size_t kInvalidSize;

// ***************************************************************************
//      型分岐用補助ツール
// ***************************************************************************

//----------------------------------------------------------------------------
//      文字列型判定(std::string, std::wstring, std::u16string, std::u32string)
//----------------------------------------------------------------------------

template<class tClass, class tEnable=void>
struct IsStringImpl : public std::false_type
{ };

template<class tClass>
struct IsStringImpl
<
    tClass,
    EnableIf
    <
           std::is_same<tClass, std::string>::value
        || std::is_same<tClass, std::wstring>::value
        || std::is_same<tClass, std::u16string>::value
        || std::is_same<tClass, std::u32string>::value
    >
> : public std::true_type
{ };

template<class tClass>
struct IsString
{
    static const bool value=IsStringImpl<tClass>::value;
};

//----------------------------------------------------------------------------
//      プリミティブ型判定(数値型と文字列型)
//----------------------------------------------------------------------------

template<typename tType, class tEnable=void>
struct IsPrimitiveImpl : public std::false_type
{ };

template<typename tType>
struct IsPrimitiveImpl
<
    tType,
    EnableIf
    <
           std::is_arithmetic<tType>::value
        || IsString<tType>::value
    >
> : public std::true_type
{ };

template<typename tType>
struct IsPrimitive
{
    static const bool value=IsPrimitiveImpl<tType>::value;
};

//----------------------------------------------------------------------------
//      侵入型と非侵入型のTheolizerVersion判定
//----------------------------------------------------------------------------

template<class tClass, class tEnable=void>
struct IsTheolizerVersionImpl : public std::false_type
{ };

template<class tClass>
struct IsTheolizerVersionImpl
<
    tClass,
    EnableIf
    <
        tClass::Theolizer::kIsVersion
    >
> : public std::true_type
{ };

template<class tClass>
struct IsTheolizerVersion
{
    static const bool value=IsTheolizerVersionImpl<tClass>::value;
};

//----------------------------------------------------------------------------
//      手動型用基底クラス(TheolizerBase)判定
//----------------------------------------------------------------------------

template<class tClass, class tEnable=void>
struct IsTheolizerBaseImpl : public std::false_type
{ };

template<class tClass>
struct IsTheolizerBaseImpl
<
    tClass,
    EnableIf<tClass::kIsTheolizerBase && !IsTheolizerVersion<tClass>::value>
> : public std::true_type
{ };

template<class tClass>
struct IsTheolizerBase
{
    static const bool value=IsTheolizerBaseImpl<tClass>::value;
};

//----------------------------------------------------------------------------
//      非侵入型生成
//----------------------------------------------------------------------------

template<class tClass>
struct NonIntrusiveImpl
{
    typedef TheolizerNonIntrusive<typename std::remove_const<tClass>::type> Type;
};

template<class tClass>
using NonIntrusive=typename NonIntrusiveImpl<tClass>::Type;

//----------------------------------------------------------------------------
//      非侵入型クラス判定
//----------------------------------------------------------------------------

template<class tClass, class tEnable=void>
struct IsNonIntrusiveImpl : public std::false_type
{ };

template<class tClass>
struct IsNonIntrusiveImpl
<
    tClass,
    EnableIf<NonIntrusive<tClass>::kIsTheolizer>
> : public std::true_type
{ };

template<class tClass>
struct IsNonIntrusive
{
    static const bool value=IsNonIntrusiveImpl<tClass>::value;
};

//----------------------------------------------------------------------------
//      侵入型判定
//----------------------------------------------------------------------------

template<class tClass, class tEnable=void>
struct IsIntrusiveImpl : public std::false_type
{ };

template<class tClass>
struct IsIntrusiveImpl
<
    tClass,
    EnableIf
    <
        std::is_class<tClass>::value
     && !IsString<tClass>::value
     && !IsNonIntrusive<tClass>::value
     && !IsTheolizerBase<tClass>::value
    >
> : public std::true_type
{ };

template<class tClass>
struct IsIntrusive
{
    static const bool value=IsIntrusiveImpl<tClass>::value;
};

//----------------------------------------------------------------------------
//      バージョンアップで削除された領域管理用クラス
//          定義された時点では領域を確保せず、get()の時点で確保する。
//          領域をポインタで確保するのでTheolizerSpecials<>をムーブ対応
//          できるようになる。
//      ムーブ可能／コピー不可
//----------------------------------------------------------------------------

//      ---<<< deleteツール >>>---
//      配列への参照メンバはTypeが配列への参照となる。
//      その時、Typeは単なる配列なので、delete[]する。

template<typename tType, class tEnable=void>
struct Deleter
{
    static void deleteMember(tType* iData)
    {
        delete iData;
    }
};

template<typename tType>
struct Deleter<tType, EnableIf<std::is_array<tType>::value> >
{
    static void deleteMember(tType* iData)
    {
        delete[] iData;
    }
};

//      ---<<< 本体 >>>---

template<typename tType>
class DeferredGeneration
{
private:
    typedef typename std::remove_reference<tType>::type Type;

    Type*   mData;

public:
    DeferredGeneration() : mData(nullptr) { }
    ~DeferredGeneration()
    {
        Deleter<Type>::deleteMember(mData);
    }

    // 領域獲得
    Type& get()
    {
        if (!mData) {
            //  (配列型へのポインタに対応するためreinterpret_castする)
            mData=reinterpret_cast<tType*>(new Type());
        }
        return *mData;
    }

    // ムーブ
    DeferredGeneration(DeferredGeneration&& ioDeferredGeneration) noexcept :
        mData(ioDeferredGeneration.mData)
    {
        ioDeferredGeneration.mData=nullptr;
    }
    DeferredGeneration& operator=(DeferredGeneration&& ioDeferredGeneration)
    {
        mData=ioDeferredGeneration.mData;
        ioDeferredGeneration.mData=nullptr;
    }

    // コピー可
    DeferredGeneration(DeferredGeneration const& iRhs)
    {
        mData=iRhs.mData;
    }
    DeferredGeneration& operator=(DeferredGeneration const& iRhs)
    {
        mData=iRhs.mData;
        return *this;
    }
};

#define THEOLIZER_INTERNAL_DEFERRED_GENERATION(dType)                       \
    theolizer::internal::DeferredGeneration<THEOLIZER_INTERNAL_UNPAREN dType>

// ***************************************************************************
//      型情報取得中継
// ***************************************************************************

//----------------------------------------------------------------------------
//      基底クラス
//----------------------------------------------------------------------------

class BaseTypeFunctions;
THEOLIZER_INTERNAL_DLL BaseTypeFunctions* getTypeFunctions();
THEOLIZER_INTERNAL_DLL void setTypeFunctions(BaseTypeFunctions* iTypeFunctions);

class BaseTypeFunctions
{
public:
    static BaseTypeFunctions const& getInstance()
    {
        BaseTypeFunctions*  ret=getTypeFunctions();
        if (!ret)
        {
            THEOLIZER_INTERNAL_ERROR(u8"BaseTypeFunctions is null.");
        }
        return *ret;
    }

    #define THEOLIZER_INTERNAL_DEF_PRIMITIVE(dType, dSimbol)                \
        virtual char const* getPrimitiveName(unsigned iSerializerVersionNo, dType) const=0;

    #define THEOLIZER_INTERNAL_DEF_STRING(dType, dSimbol)                   \
        virtual char const* getPrimitiveName(unsigned iSerializerVersionNo, dType const&) const=0;

    #include "primitive.inc"

    virtual char const* getCppName
    (
        std::string const& iPrimitiveName,
        unsigned iSerializerVersionNo
    ) const=0;

    virtual std::type_index getStdTypeIndex() const=0;
    virtual unsigned getLastVersionNo()       const=0;
    virtual char const* getSerializerName()   const=0;
};

//----------------------------------------------------------------------------
//      現在有効な派生Serializer
//----------------------------------------------------------------------------

template<class tMidSerializer>
class TypeFunctions : public BaseTypeFunctions
{
    BaseTypeFunctions*  mBackup;
public:
    // 登録
    TypeFunctions()
    {
        mBackup=getTypeFunctions();
        setTypeFunctions(this);
    }
    // 解除
    ~TypeFunctions()
    {
        setTypeFunctions(mBackup);
    }

    #define THEOLIZER_INTERNAL_DEF_PRIMITIVE(dType, dSimbol)                \
        char const* getPrimitiveName(unsigned iSerializerVersionNo, dType) const\
        {                                                                   \
            return tMidSerializer::template getPrimitiveName<dType>(iSerializerVersionNo);\
        }
    #define THEOLIZER_INTERNAL_DEF_STRING(dType, dSimbol)                   \
        char const* getPrimitiveName(unsigned iSerializerVersionNo, dType const&) const\
        {                                                                   \
            return tMidSerializer::template getPrimitiveName<dType>(iSerializerVersionNo);\
        }

    #include "primitive.inc"

    char const* getCppName
    (
        std::string const& iPrimitiveName,
        unsigned iSerializerVersionNo
    ) const
    {
        return tMidSerializer::getCppName(iPrimitiveName, iSerializerVersionNo);
    }

    std::type_index getStdTypeIndex() const {return std::type_index(typeid(tMidSerializer));}
    unsigned getLastVersionNo()       const {return tMidSerializer::kLastVersionNo;}
    char const* getSerializerName()   const {return tMidSerializer::kSerializerName;}
};

#endif  // THEOLIZER_INTERNAL_DOXYGEN
}   // namespace internal

//############################################################################
//      End
//############################################################################

}   // namespace theolizer

// ***************************************************************************
//          DLL用の警告禁止解除
// ***************************************************************************

#ifdef _MSC_VER
  #pragma warning(pop)
#endif

#endif  // THEOLIZER_INTERNAL_CORE_ASSORTED_H