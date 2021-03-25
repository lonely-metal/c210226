/*
*   210226: 新規追加
*   210322: githubで管理出来るよう設定
*
*   C++ 11/14/17/20 新しい仕様の使い方を覚えていく
* 
*   includeに追加： C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.27.29110\include
*   libに追加：     C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.27.29110\lib\x86
*/

#include <cstdio>   // stdio.hの代わりにこちらをinclude
#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <string>
#include <set>
#include <deque>
#include <time.h>
#include <algorithm>
#include <functional>
#include <thread>
#include <random>
#if __has_include("c210225.h")  // includeファイルが無いかどうか判定する
#include "c210225.h"
#else
#include "c210226.h"
#endif
//#include <source_location>    // 無い

#if __has_include(<has_include.hpp>)
#  warning <has_include.hpp> is found
#else
//#  warning <has_include.hpp> is not found // プリプロセッサ コマンド 'warning' が無効です。 
#endif

using namespace std::literals::chrono_literals;
using namespace std::string_literals;

/*
* https://cpprefjp.github.io/lang/cpp11/auto.html
*/
void about_auto() {
    auto i = 0;                         // i は int 型
    const auto l = 0L;                  // l は const long 型
    auto& r = i;                        // r は int& 型
    auto s = "";                        // s は const char* 型
    auto p = std::make_pair(1, 'c');    // p は std::pair<int, char> 型
    auto q = std::make_shared<int>(42); // q は std::shared_ptr<int> 型
    auto z = { 1.0, 2.0, 3.0, };        // z は std::initializer_list<double> 型
    auto f = [] {};                      // f は 引数を取らずに値を返さない operator() を持つユニークなクロージャ型
}

// [[noreturn]]属性 関数が決して返らないことを示すための属性
[[noreturn]]void noreturn_func()
{
	throw std::runtime_error("runtime error\n");	// 実行時に異常終了起こす
}

void func()
{
	{
		// [[noreturn]]属性
		bool b=true;
		if(false == b){
			printf("noreturn route\n");
			noreturn_func();
		}
	}
    char* ptr = nullptr;    // NULL→nullptr
    char ary[200];
    sprintf_s(ary, "ABC");   // sprintf()→sprintf_s()

    ptr = ary;
    if (nullptr != ptr)
    {
        printf("%s\n", ptr);
    }

    {
        int iAry[] = { 1, 2, 3 };   // 統一初期化記法(Uniform Initialization)
        for (const int& cnt : iAry)   // 範囲ベースの for-loop
        {
            printf("%d ", cnt);
        }
        printf("\n");
    }

    //int i; scanf_s("%d", &i);   // この1行で実行を止める

    std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7 };  // 初期化子リスト (initializer lists) ユーザー定義型のオブジェクトに対して、波カッコによるリスト初期化を使用できるようにするようオーバーロードする機能
    for (const auto& x : v) {   // 型推測autoも使える
        std::cout << x;
    }
    printf("\n");

    {
        enum engName {
            eThink = 0,
            eGuess,
            eSuggest,
            eMax
        };
        std::map<engName, std::string> mp;  // std::map(C#のDictionaryみたいなもの)
        mp[eThink] = "思う";
        mp[eGuess] = "推測する";
        mp[eSuggest] = "提案する";
        for (int cnt = 0; cnt < eMax; cnt++) {
            printf("%s\n", mp[(engName)cnt].c_str());
        }
    }

    std::set<int>setInt{ 3,7,1,2,9,8 }; // std::set　まだ使い道がピンと来ない。。
    for(int cnt = 0; cnt < 10; cnt++){
        std::set<int>::iterator setItr = setInt.find(cnt);
        if (setItr == setInt.end()) {
            printf("%d not found\n", cnt);
        }
        else {
            printf("%d found\n", cnt);
        }
    }

    std::vector<int> vecInt{ 3, 4, 5 };
    //vecInt.push_front(2);     // vectorではpush_front()が使えない
    vecInt.emplace_back(6);
    printf("size %llu\n", vecInt.size());
    for (int cnt = 0; cnt < vecInt.size(); cnt++) {
        printf("%d\n", vecInt[cnt]);
    }

    int decltypeInt = 1;
    decltype(decltypeInt) decltypeInt2 = 2; // int型になる
    printf("%d\n", decltypeInt2);
    std::string decltypeStr = "ZZZ";
    decltype(decltypeStr) decltypeStr2 = "XXX"; // string型になる
    printf("%s\n", decltypeStr2.c_str());

    std::vector<std::string> vecStr;
    vecStr.emplace_back("AAA");
    vecStr.emplace_back("BBB");
    vecStr.emplace_back("CCC");
    for (const auto& cnt : vecStr) {    // 範囲for文
        printf("%s\n", cnt.c_str());
    }

    time_t t;
    time(&t);
    const int constInt = (int)t;                // constは変数で初期化出来る
    printf("%d\n", constInt);
    //constexpr int constexprInt = (int)t;      // constexprはエラーになる
    constexpr int constexprInt = 100;
    printf("%d\n", constexprInt);

    int iInit{ 33 };    // 非静的メンバ変数の初期化
    printf("%d\n", iInit);
}

void     lambdaExpressions() {

    auto plus = [](int a, int b) { return a + b; }; // ラムダ式
    int result = plus(2, 3); // result == 5
    printf("%d\n", result);

    int x = 88;
    printf("%d\n", x);
    auto func = [&] { x = 89; };
    func();
    printf("%d\n", x);

    x = 90;
    printf("%d\n", x);
    auto func2 = [=] { return x + 1; };
    int xx = func2();
    printf("%d\n", xx);

    enum eNum1{Red=0, Orange, Yellow};
    //enum eNum2{Red=1, Orange, Yellow};  // // Redを2重定義してるためエラー
    eNum1 e1 = Red;
    int i = (int)e1;
    printf("%d\n", i);

    enum class eNumC1{Red, Orange, Yellow};  // スコープを持つ列挙型
    enum class eNumC2{Red, Orange, Yellow};  // スコープを持つ列挙型
    eNumC1 ec1 = eNumC1::Orange;
    eNumC2 ec2 = eNumC2::Yellow;
    i = (int)eNumC1::Orange;    // C++11の説明ではエラーになるようなこと書いてるけどOKやった
    printf("%d\n", i);          
    printf("%d\n", (int)ec1);   // C++11の説明ではエラーになるようなこと書いてるけどOKやった
}

class Base1 {
public:
    Base1() {}
    Base1(int) {}
};
class Base2 {
public:
    Base2() {}
    Base2(const std::string&) {}
};
class Derived1 : Base1, Base2 {
public:
    using Base1::Base1;     // Derived d2(3);が有効になる
    using Base2::Base2;     // Derived d3("Hello!");が有効になる
};
void inheritingConstructors() { // 継承コンストラクタ
    Derived1 d1;
    Derived1 d2(3);
    Derived1 d3("Hello!");
}

class Base3 {
public:
    virtual void funcNormal() {}
    virtual void funcFinal() final {}
};
class Derived3 : Base3 {
public:
    virtual void funcNormal() override;
    virtual void funcNormal2();
    //virtual void funcNormal3() override;  // 基底クラスにfuncNormal3()が存在しないためエラーとなる
    //virtual void funcFinal();             // 基底クラスでfinal指定してるためオーバーライド出来ない
};

union uNion {
    unsigned int    ui;
    unsigned char   uc[4];
    std::string     st; // 共用体の制限解除 共用体のメンバ変数として、クラスオブジェクトを保持できるようになった    

    uNion() : ui(0) {}  // これが無いとエラーになる
    ~uNion() {}         // これが無いとエラーになる
};

void unionConfirm() {
    
    uNion u;
    u.ui = 0x12345678;
    printf("%x %x %x %x\n", u.uc[0], u.uc[1], u.uc[2], u.uc[3]);
}

int returnFunc1()
{
    return 21;
}
auto returnFunc2() -> int   // 戻り値の型を後置する関数宣言構文
{
    return 22;
}
auto returnFunc3(int x) -> std::string
{
    return "return";
}
void returnFunc() {
    printf("%d\n", returnFunc1());
    printf("%d\n", returnFunc2());
    printf("%s\n", returnFunc3(1).c_str());
}

#define DEBUG_LOG( fmt, ... )  printf( "[%s] %s() %05d: "fmt,__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__ ) // 可変引数マクロ

void func2() {
    std::string json = "{\"user_id\": 123, \"name\": \"Alice\"}";
    printf("%s\n", json.c_str());
    std::string json2 = R"({"user_id": 123, "name": "Alice"})"; // 生文字列リテラル(Rプレフィックス)
    printf("%s\n", json2.c_str());

    DEBUG_LOG("%d %d %s", 1, 2, "DEBUG_LOG");   // 可変引数マクロ

    std::array<int, 5> stAry{ 1, 2, 3, 4, 5 };    // std::array
    for (int i = 0; i < stAry.size(); i++) {    
        printf("%d\n", stAry[i]);   // std::arrayは整列されない？！
    }
    std::vector<int> stVec{ 1, 2, 3, 4, 5 };
    for (int i = 0; i < stVec.size(); i++) {
        printf("%d\n", stVec[i]);
    }

    std::vector<int> feVec{ 9, 8, 7, 6, 5 };
    auto feFunc = [](int i) { printf("%d\n", i); }; // ラムダ式
    std::for_each(feVec.begin(), feVec.end(), feFunc);  // for_each()

    std::vector<std::string> feVec2{ "AAA", "BBB", "CCC"};
    auto feFunc2 = [](std::string st) { printf("%s\n", st.c_str()); }; // ラムダ式
    std::for_each(feVec2.begin(), feVec2.end(), feFunc2);  // for_each()

    std::shared_ptr<int> sp1(new int(333));
    printf("%d\n", *sp1);
    std::shared_ptr<int> sp2 = sp1;     // shared_ptrはポインタのコピー可能
    *sp2 = 444;
    printf("%d\n", *sp1);

    std::unique_ptr<int> up1(new int(555));
    printf("%d\n", *up1);
    if (up1 == nullptr) {
        printf("%d: nullptr\n", __LINE__);
    }
    //std::unique_ptr<int> up2 = up1;           // unique_ptrはポインタのコピーが出来ない
    std::unique_ptr<int> up2(std::move(up1));   // unique_ptrはポインタのmoveは可能
    if (up1 == nullptr) {
        printf("%d: nullptr\n", __LINE__);      // move後、コピー元のup1は空っぽ
    }

    int i = 555;
    std::string stToStr = std::to_string(i);    // std::to_string()
    printf("%s\n", stToStr.c_str());
    i = std::stoi("444");                       // std::stoi()
    printf("%d\n", i);

    std::function<void(int)>func1 = feFunc;         // std::function() 関数を代入
    func1(6);
    std::function<int(void)>func2 = returnFunc1;    // std::function() 関数を代入
    printf("%d\n", func2());
    std::function<int(int, int)>func3 = [](int a, int b) -> int { return a + b; };     // std::function() 関数オブジェクトを代入
    printf("%d\n", func3(3, 7));

    // std::bind() 
    // オブジェクトに対し、引数を部分的に束縛(bind)する。
    //
    // 使い所としては、bindBase()の3つの引数の出どころが別部署にまたがってて、1つ目と2つ目をセットしたあと、
    // 3つ目は違う部署のプログラムがセットするとか？！
    auto bindBase = [](int a, int b, int c) -> int { return (a + b + c); };
    printf("%d\n", bindBase(1, 2, 3));
    std::function<int(int)> bind1 = std::bind(bindBase, 1, 2, std::placeholders::_1);   // 部署Aで設定
    printf("%d\n", bind1(3));   // 部署Bで設定

    auto threadFunc = []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        printf("%s\n", __FUNCTION__);
    };
    std::thread th1(threadFunc);    // std::threadは、新しい実行のスレッド(thread of execution)（以下、単にスレッドとする）の作成／待機／その他操作を行う機構を提供
    printf("%s\n", __FUNCTION__);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    th1.join(); // th1()の実行が終わってなければこのタイミングで実行。終わってれば何もしない。


    std::tuple<int, double, std::string> tpl = std::make_tuple(1, 2, "foo");    // tuple
    printf("%d\n", std::get<0>(tpl));
    printf("%f\n", std::get<1>(tpl));
    printf("%s\n", std::get<2>(tpl).c_str());

    std::vector<std::tuple<int, double, std::string>> tplVec;   // tuple
    for (int i = 0; i < 3; i++)
    {
        tplVec.emplace_back(i, (double)i, "foo");
    }
    for (int i = 0; i < tplVec.size(); i++) {
        printf("%d %f %s\n", std::get<0>(tplVec[i]), std::get<1>(tplVec[i]), std::get<2>(tplVec[i]).c_str());
    }

    std::random_device rnd;     // random
    for (int i = 0; i < 10; i++) {
        printf("%d\n", rnd());
    }
    for (int i = 0; i < 10; i++) {
        printf("%d\n", rnd()%100);
    }
}

// [[deprecated]]属性 https://cpprefjp.github.io/lang/cpp14/deprecated_attr.html
//[[deprecated("この関数は削除すべき")]]  Visual Studioだと警告では無く、エラーになる
void old_func()
{}

class AAA {
public:
    AAA(int i) {
        printf("AAA constructor %d\n", i);
    }
    ~AAA()
    {
        printf("AAA destructor()\n");
    }
private:
    int pi;
};
void     makeUniquePtrFunc() {
    std::unique_ptr<AAA> uniNptr(new AAA(1));
    std::unique_ptr<AAA> uniMptr(std::make_unique<AAA>(2)); // std::make_unique
}

class BBB {
public:
    BBB(int i) {
        pr_uni_ptr = std::make_unique<AAA>(i);
    }
private:
    std::unique_ptr<AAA> pr_uni_ptr;
};
void uniquePtr() {
    printf("line: %d\n", __LINE__);
    //BBB* bbb = new BBB(3);    古い書き方
    BBB* bbb{ new BBB(3) };
    printf("line: %d\n", __LINE__);
    delete bbb;     // このタイミングでstd::make_unique<AAA>(i)に対するデストラクタが呼ばれる
    printf("line: %d\n", __LINE__);
}
void uniquePtr2() {
    printf("line: %d\n", __LINE__);
    std::unique_ptr<BBB> bbb(std::make_unique<BBB>(4));
    printf("line: %d\n", __LINE__);
}   // このタイミングでstd::make_unique<AAA>(i)に対するデストラクタが呼ばれる

std::tuple<int, int, std::string> structBindingTest() { // 構造化束縛
    return{ 1, 2, "Message" };
}
int no_nodiscardTest() {
    return 1;
}
[[nodiscard]]
int nodiscardTest() {   // [[nodiscard]]属性
    return 1;
}
int retSwitchFunc() {
    return 3;
}
namespace nAAA::nBBB::nCCC  // 入れ子名前空間の定義
{
    void namespaceFunc() {
        printf("%s\n", __FUNCTION__);
    }
}
void exceptionFunc() noexcept(false) {  // 例外が発生するかも知れない
    throw "the end";
}
void exceptionFunc2() noexcept(true) {  // 例外が発生しないことを明示
    throw "the end";	// warning C4297
}
class referenceTest {
public:
    referenceTest(std::string s) {
        name = s;
    }
    std::string getString() {
        return name;
    }
    const std::string& getString2() {
        return name;    // 参照渡ししている
    }
private:
    std::string name;
};
void vectorFunc(std::vector<int>& vecInt) {
    for (int i = 0; i < vecInt.size(); i++) {
        printf("%d\n", vecInt[i]);
    }
}
void vectorFunc2(std::vector<int>& vecInt) {
    vecInt.emplace_back(44);
}

class delegatingConstructor {
public:
    delegatingConstructor(int x, int y, int z) {
        printf("%d = %d * %d * %d\n", x * y * z, x, y, z);
    }
    delegatingConstructor() : delegatingConstructor(3, 3, 3) {} // 委譲コンストラクタ
    delegatingConstructor(int i) : delegatingConstructor(i, 3, 3) {} // 委譲コンストラクタ
    delegatingConstructor(int i, int j) : delegatingConstructor(i, j, 3) {} // 委譲コンストラクタ
    delegatingConstructor(std::vector<int> v) : delegatingConstructor(v[0], v[1], v[2]) {}  // 委譲コンストラクタ
};

class inheritingConstructor : public delegatingConstructor {
public:
    using delegatingConstructor::delegatingConstructor; // 継承コンストラクタ
};

class friendTest {
public:
    friend void friendFunc(friendTest& f);  // friend
private:
    void func() {
        printf("friendTest\n");
    }
};
void friendFunc(friendTest& f) {    // friend
    f.func();
}
template <typename X> void templateFunc(X x) {  // template
    std::cout << x << "\n";
}

void uniquePtrFunc(std::unique_ptr<int>& up) {
    *up = 10;
}

class uniquePtrClass {
public:
    std::unique_ptr<int> getPtr() {
        std::unique_ptr<int> up = std::make_unique<int>();
        return(std::move(up));
    }
private:
    std::unique_ptr<int> ptr;
};
std::unique_ptr<uniquePtrClass> getUniquePtrClass() {
    std::unique_ptr<uniquePtrClass> up = std::make_unique<uniquePtrClass>();
    return(std::move(up));
}
void vectorArgFunc(std::vector<int>& vi) {
    for (int i = 0; i < vi.size(); i++) {
        printf("%d\n", vi[i]);
    }
}

template<typename retType>
retType templateTest(int i, double d) {

    if (i > d) {
        return i;
    }
    else {
        return d;
    }
}

// 戻り値の型を後置する関数宣言構文
template<typename argType1, typename argType2>
auto returnDeclFunc(argType1 a1, argType2 a2) -> decltype(a1 + a2) { return(a1 + a2); }

void func3() {

    std::chrono::seconds sec(10);   // std::chrono::duration
    std::chrono::minutes min(3);    // std::chrono::duration

    // 結果の型はstd::chrono::seconds
    auto result = sec + min;
        // 190
    printf("%lld\n", result.count());

    inlineValueTest i;
    inlineTestFunc(i);
    printf("%d\n", i.i);

    auto [no, address, name] = structBindingTest();     // 構造化束縛
    printf("%d %d %s\n", no, address, name.c_str());

    no_nodiscardTest();
    nodiscardTest();    // warning C4834: 'nodiscard' 属性を持つ関数の戻り値を破棄しています

    if (int i = retSwitchFunc(); i) // if文とswitch文の条件式と初期化を分離
    {
        printf("%d\n", i);
    }
    switch (int i = retSwitchFunc(); i) // if文とswitch文の条件式と初期化を分離
    {
    case 0:
        break;
    case 3:
        printf("%d\n", i);
        break;
    default:
        break;
    }

    nAAA::nBBB::nCCC::namespaceFunc();  // 入れ子名前空間の定義

    int initI1{};
    int initI2(int{});
    int initI3(int{ 256 });
    printf("%d %d %d\n", initI1, initI2, initI3);

    using MyInt = int;  // typedefは使うな usingを使え
    MyInt mi = 49;

    try {
        exceptionFunc();
    }
    catch (...) {
        printf("exception err: %d\n", __LINE__);
    }
    try {
        //exceptionFunc2();     // noexcept宣言してて例外が発生したら、std::terminate()が呼ばれてcatchしない
    }
    catch (...) {
        printf("exception err: %d\n", __LINE__);
    }

    referenceTest rt("AAA");
    printf("%s\n", rt.getString().c_str());
    printf("%s\n", rt.getString2().c_str());

    std::vector<int> vecInt = {};
    vecInt.emplace_back(22);
    vecInt.emplace_back(22);
    vectorFunc(vecInt);
    vectorFunc2(vecInt);
    for (int i = 0; i < vecInt.size(); i++) {
        printf("%d\n", vecInt[i]);
    }

    std::vector<int> vecShuffle{0, 1, 2, 3, 4};
    std::random_device rnd;
    std::mt19937 get_rand_mt(rnd());    // 初期化でrandom_device使わないと毎回同じような順番でシャッフルされる
    std::shuffle(vecShuffle.begin(), vecShuffle.end(), get_rand_mt);    // 中身をシャッフル
    auto vecShuffleDisp = [](int i) {  printf("%d\n", i);   };
    std::for_each(vecShuffle.begin(), vecShuffle.end(), vecShuffleDisp);

    printf("char: %d\n", static_cast<int>(alignof(char)));
    printf("short: %d\n", static_cast<int>(alignof(short)));
    printf("int: %d\n", static_cast<int>(alignof(int)));
    printf("long: %d\n", static_cast<int>(alignof(long)));
    printf("double: %d\n", static_cast<int>(alignof(double)));

    // ラムダ関数
    int li{ 0 };
    int li2{ 100 };
    int li3{ 100 };
    auto lambdaFunc1 = [&li]() { li++;  return(li); };  // [&]にした場合、スコープ内の変数の値を書き換えることが出来る
    printf("%d\n", lambdaFunc1());
    auto lambdaFunc2 = [&]() { return(li + li2 + li3); };
    printf("%d\n", lambdaFunc2());
    auto lambdaFunc3 = [=]() {return(li + 1); };   // [=]にした場合、スコープ内の変数は入力値としてだけ使用できる。 li++とかは無理。
    printf("%d\n", lambdaFunc3());

    delegatingConstructor   d1{};   // 委譲コンストラクタ
    delegatingConstructor   d2{ 5 };    // 委譲コンストラクタ
    delegatingConstructor   d3{ 5, 5 }; // 委譲コンストラクタ
    delegatingConstructor   d4{ 5, 5, 5 };  // 委譲コンストラクタ
    std::vector<int> delVec{ 1, 2, 3 };
    delegatingConstructor   d5{ delVec };   // 委譲コンストラクタ

    friendTest f;
    friendFunc(f);  // friend

    inheritingConstructor   i1{};   // 継承コンストラクタ
    inheritingConstructor   i2{5};  // 継承コンストラクタ
    inheritingConstructor   i3{5, 5};   // 継承コンストラクタ
    inheritingConstructor   i4{5, 5, 5};    // 継承コンストラクタ
    inheritingConstructor   i5{ delVec };   // 継承コンストラクタ

    // ラムダ関数
    []() {};
    []() {}();
    []() {printf("Hello Lambda world\n"); }();

    templateFunc(1);        // template
    templateFunc("AAA");    // template
    enum{ eName1, eName2};
    templateFunc(eName2);   // ローカル型と無名型を、テンプレート引数として使用することを許可

    long long ll = 0xffff;  // long long型
    printf("%llx %lld\n", ll, ll);
    ll = 0xffffffff;
    printf("%llx %lld\n", ll, ll);
    ll = 0x7fffffffffffffff;
    printf("%llx %lld\n", ll, ll);
    ll = 0xffffffffffffffff;
    printf("%llx %lld\n", ll, ll);

    std::unique_ptr<int> up = std::make_unique<int>(1);
    printf("%d\n", *up);
    uniquePtrFunc(up);
    printf("%d\n", *up);

    uniquePtrClass uc;
    std::unique_ptr<int> up2 = uc.getPtr();
    *up2 = 100;
    printf("%d\n", *up2);

    std::unique_ptr<uniquePtrClass> ucp;
    ucp = getUniquePtrClass();
    up2 = ucp->getPtr();
    *up2 = 200;
    printf("%d\n", *up2);

    std::vector<int> vi{ 22, 33, 44 };
    vectorArgFunc(vi);

    //char utf8s[] = u8"あいうえお";   // コンパイラをlatestにすると、charだとエラー出る
    char8_t utf8s[] = u8"あいうえお";   // UTF-8文字列リテラル
    //printf("%s\n", utf8s);  // ※DOSコマンドプロンプトはS-Jisなので文字化ける
    //char utf8s2[] = u8"\U00020BB7野家"; // コンパイラをlatestにすると、charだとエラー出る
    char8_t utf8s2[] = u8"\U00020BB7野家"; // UTF-8文字列リテラル
    //printf("%s\n", utf8s2);   // ※DOSコマンドプロンプトはS-Jisなので文字化ける
        

    // using namespace std::literals::chrono_literals;
    sec = 30s;
    auto msec = 150ms;
    auto sec_msec = sec + msec;
    printf("%lld\n", sec_msec.count());

    int ti = 100;
    double td = 50.5;
    std::cout << templateTest<int>(ti, td) << "\n"; // 戻り値がtemplateの場合、呼び出し時に<int>と明示する必要がある
    td = 500.5;
    std::cout << templateTest<double>(ti, td) << "\n";  // 戻り値がtemplateの場合、呼び出し時に<double>と明示する必要がある

    // 戻り値の型を後置する関数宣言構文
    printf("%d\n", returnDeclFunc(1, 2));
    printf("%f\n", returnDeclFunc(1, 2.2));
    printf("%f\n", returnDeclFunc(1.1, 2));
    printf("%f\n", returnDeclFunc(1.1, 2.2));

    int stdInt = 100;
    //int&& rightInt = stdInt;    // 右辺値参照
    int&& rightInt = 300;
    //rightInt = std::move(stdInt);
    //int&& rightInt = std::move(stdInt); // 右辺値参照・ムーブセマンティクス ぜんぜんまだ理解出来てない
    printf("%d %d\n", stdInt, rightInt);

    constexpr bool assertFlg = true;    // 変数にconstexprつけないとエラーになる
    //constexpr bool assertFlg = false;    // true→falseに書き換えた時点でコンパイルエラーになる
    static_assert(assertFlg, "コンパイル時アサート");
    static_assert(assertFlg);   // 第2引数に診断メッセージを指定しなければならなかった。 C++17 ではこれを省略できるようになった。
}

template <class T>
using Vec = std::vector<T>; // エイリアステンプレート

void variadicFunc() {   // 可変引数テンプレート
    printf("\n");
}
template <class Head, class... Body>    // 可変引数テンプレート
void variadicFunc(Head&& head, Body... body) {  // 可変引数テンプレート
    std::cout << head << " ";
    variadicFunc(body...);  // 再帰関数
}

class uniquePtrTest {
public:
    uniquePtrTest() {
        printf("%s\n", __FUNCTION__);
    }
    ~uniquePtrTest() {
        printf("%s\n", __FUNCTION__);
    }
};
class uniqueTestClass {
public:
    uniqueTestClass(){
        printf("%s\n", __FUNCTION__);
        up = std::make_unique<uniquePtrTest>(); // このunique_ptrが解放されるのはuniqueTestClassのデストラクタが終了した後
                                                // つまりコンストラクタ抜けた後も持続してる
    }
    ~uniqueTestClass() {
        printf("%s\n", __FUNCTION__);
    }
private:
    std::unique_ptr<uniquePtrTest> up;
};
void uniqueTestFunc() {
    printf("%d %s\n", __LINE__, __FUNCTION__);
    uniqueTestClass utc;
    printf("%d %s\n", __LINE__, __FUNCTION__);
}

template<class T>   // テンプレートクラス
class templateClassTest {
public:
    templateClassTest(T t) {
        value = t;
    }
    void func() {
        std::cout << value << "\n";
    }
private:
    T value;
};
class unique_ptrTest {
public:
    int getA() const{   // const付加しないとコンパイルエラー(C2662)になる
        return a;
    }
    void putA(int i) {
        a = i;
    }
    void putB(int i) {
        b = i;
    }
    void print() {
        printf("%d %d\n", a, b);
    }
private:
    int a;
    int b;
};

template <class T>  // class TのTは何度でも使える
void templateTest(T t) {
    std::cout << t << std::endl;
}
template <class T>  // class TのTは何度でも使える
void templateTest2(std::vector<T> vt) {
    for (const auto& cnt : vt) {    // 範囲for文
        std::cout << cnt << std::endl;
    }
}
class defaultDeleteTest {
public:
    defaultDeleteTest() = default;  // コンストラクタはそのまま
    defaultDeleteTest(const defaultDeleteTest&) = delete;   // コピーコンストラクタは使用禁止
    virtual ~defaultDeleteTest() = default; // デストラクタはvirtualにする
};

void func4() {
    Vec<std::string> vecSt{"AAA", "BBB", "CCC"};    //  エイリアステンプレート
    for (int i = 0; i < vecSt.size(); i++) {
        printf("%s\n", vecSt[i].c_str());
    }

    variadicFunc(111);  // 可変引数テンプレート
    variadicFunc(111, 222, 333);    // 可変引数テンプレート
    variadicFunc(111, 555, "string", 7.77); // 可変引数テンプレート

    printf("%d\n", __LINE__);
    uniqueTestFunc();
    printf("%d\n", __LINE__);

    {
        int i = 0B010010001;    // 2進数リテラル
        printf("%d 0x%x\n", i, i);
    }

    {
        // 通常関数の戻り値型推論
        auto func = [](int a) -> auto{ return (a + 1); }; // ラムダ式
        printf("%d\n", func(100));
        auto func2 = [](int a) -> decltype(auto) { return (a + 1); }; // ラムダ式
        printf("%d\n", func2(200));
    }
    {
        // ジェネリックラムダ
        auto func = [](auto a, auto b) -> auto{ return (a + b); };
        printf("%d\n", func(10, 10));
        printf("%f\n", func(10.1, 10.1));
        //printf("%s\n", func("AAA", "BBB").c_str());   // ここ実装すると上記のb変数でエラーでる
        //std::string st = func("AAA", "BBB");          // ここ実装すると上記のb変数でエラーでる
        std::string st = func("AAA"s, "BBB"s);          // using namespace std::string_literals;
        printf("%s\n", st.c_str());
    }
    {
        // const変数
        std::random_device rnd;
        int i = rnd() % 100;
        const int ci = i;   // コンパイル時ではなく実行時に値が決まる
        printf("%d\n", ci);
    }
    {
        // 関数のconstexpr
        auto constexprFunc = [](int i) constexpr { return(sizeof(int) * i * 4); };
        int ii = 2;
        //constexpr int ci = constexprFunc(ii);   // 引数を変数にするとエラー
        constexpr int ci = constexprFunc(2);
        printf("%d\n", ci);
    }
    {
        // 数値リテラルの桁区切り文字
        int i = 1'000'000;
        printf("%d\n", i);
        i = 0b0110'0011;
        printf("0x%x\n", i);
    }
    {
        // テンプレートクラス
        templateClassTest t1{ 333 };
        t1.func();
        templateClassTest t2{ 5.5 };
        t2.func();
        templateClassTest t3{ "Hello template class world" };
        t3.func();
    }
    {
        // [[maybe_unused]]属性
        [[maybe_unused]] int i = 0; // 警告が出ない
        int ii = 0; // 'ii': ローカル変数が初期化されましたが、参照されていません
    }
    {
        // enum class変数の初期値として整数を指定する際の規則を調整
        enum class byte : unsigned char { };
        byte ba{ (byte)42 };    // C++14でOK
        byte bc{ 42 };  // C++14だとエラー、C++17だとOK
    }
    {
        // 初期化式をともなう範囲for文(C++20)
        std::vector<std::string> vec{ "AAA", "BBB", "CCC" };
        for (auto i = 1; auto & x : vec) {
            printf("%d: %s\n", i, x.c_str());
            i++;
        }
    }
    {
        // source_location(C++20)
        //std::cout << location.line() << std::endl;    // 210318現在、実装されてない
    }
    {
        // 7分でわかる右辺値参照
        // 左辺値参照は、右辺値を初期化に使えないようにする
        // 右辺値参照は、左辺値を初期化に使えないようにする
        int i = 10;
        auto f = []() -> int {return 2; };
        //int& lref = 1;    // エラー 1は右辺値なので初期化に使えない
        //int& lref = f();  // エラー f()は右辺値なので初期化に使えない
        int& lref = i;
        printf("%d %d\n", i, lref);
        i = 50;
        printf("%d %d\n", i, lref);
        lref = 100;
        printf("%d %d\n", i, lref);

        //int&& rref = lref;    // エラー lrefは左辺値なので初期化に使えない
        //int&& rref = i;       // エラー iは左辺値なので初期化に使えない
        int&& rref = f();
        int&& rref2 = 2;
        int&& rref3 = std::move(i);     // iを右辺値に変えたらOK
    }
    {
        // スマートポインタ
        auto f = [](std::unique_ptr<int>& i) { *i = 10; };
        std::unique_ptr<int> ut = std::make_unique<int>();
        f(ut);
        printf("%d\n", *ut);

        auto uf = [](std::unique_ptr<unique_ptrTest>& upt) { upt->putA(20); };
        std::unique_ptr<unique_ptrTest> uct = std::make_unique <unique_ptrTest>();
        uf(uct);
        uct->putB(30);
        uct->print();

    }
    {
        // ポインタ変数使わなくても参照渡しのみでコーディング可能
        auto f = [](unique_ptrTest& up) { up.putA(40); up.putB(50); };
        unique_ptrTest uc;
        f(uc);
        uc.print();
    }
    {
        // 関数の中で値を更新されたくない場合
        auto f = [](const unique_ptrTest& up) -> int { return(up.getA()); };    // constクラス変数を引数にする場合、関数内で使用するメンバー関数はconst宣言する必要がある
        unique_ptrTest uc;
        uc.putA(999);
        uc.putB(f(uc));
        uc.print();
    }
    {
        // template関数
        templateTest(100);
        templateTest(200.22);
        std::vector<double> vd{ 1.1, 2.2, 3.3 };
        templateTest2(vd);
        std::vector<std::string> vs{ "111", "222", "333" };
        templateTest2(vs);
    }
    {
        defaultDeleteTest d;
        //defaultDeleteTest dd = d;   // コピーコンストラクタはdelete宣言してるのでコンパイルエラー
    }
    {
        // 関数オブジェクト
        struct funcObject {
            auto operator()(int x) -> void {
                printf("%s %d\n", __FUNCTION__, x);
            };
        };
        funcObject fo;
        fo(10);
        struct funcObject2 {
            auto operator()() -> int {
                return 555;
            };
        };
        funcObject2 fo2;
        printf("%d\n", fo2());

        // ラムダ式
        std::vector<int> vec{ 100, 200, 300, 400 };
        std::for_each(vec.begin(), vec.end(),
            [](int x) {printf("%d\n", x); });

        // autoの使い所
        auto f = []() {return 0x1ffffffff; };
        int i = f();    // intで決め打ちするとオーバーフローしたとき値を保持できない
        //printf("0x%llx\n", i);	// warning C4477
        printf("0x%x\n", i);
        auto a = f();   // long long int型として値を保持
        printf("0x%llx\n", a);

        // autoの使い所
        auto up = std::make_unique<int>(10);    // 明らかにunique_ptr<int>だと言うことが分かる
        printf("%d\n", *up);

        // ラムダ式変数のキャプチャ
        int i1 = 100;
        int i2 = 200;
        //auto l = []() {printf("%d\n", i1); }; // エラー、ラムダ関数の中でi1は見えない
        auto l = [&]() { printf("%d\n", i1); }; // [&]と宣言することでローカル変数を参照出来るようになる
    }
    {
        // 構造化束縛(tuple)
        auto f = []() -> std::tuple<int, double, std::string> { return{ 50, 6.6, "AAA" }; };
        auto[i, d, s] = f();
        printf("%d %f %s\n", i, d, s.c_str());
    }
    {
        // 乱数
        std::random_device rnd;     // mt19937よりも遅いらしい
        for (int i = 0; i < 10; i++) {
            printf("%d ", rnd()%100);
        }
        printf("\n");

        std::mt19937 mt(rnd());     // こうするのがbetterか
        for (int i = 0; i < 10; i++) {
            printf("%d ", mt() % 100);
        }
        printf("\n");

        // ベルヌーイ分布(指定した確率でtrueを出す)
        std::bernoulli_distribution dist(0.7);  // 70%
        for (int i = 0; i < 10; i++) {
            printf("%s ", (dist(mt)) ? "T" : "_");
        }
        printf("\n");

        // ベルヌーイ分布(指定した確率でtrueを出す)
        std::bernoulli_distribution dist2(0.1); // 10%
        for (int i = 0; i < 10; i++) {
            printf("%s ", (dist2(mt)) ? "T" : "_");
        }
        printf("\n");

        // 正規分布
        std::normal_distribution<float> dist3(0.0, 1.0);
        for (int i = 0; i < 10; i++) {
            printf("%f ", dist3(mt));
        }
        printf("\n");

        // 範囲forループ
        int scores[5]{ 10, 20, 30, 40 ,50 };
        for (auto& score : scores) {
            score += 1;
        }
        for (const auto& score : scores) {
            printf("%d\n", score);
        }
    }
    {
        // 二重ループ
        int ary[3][5]{};
        for (int cnt = 0; auto & i : ary) {
            for (auto& j : i) {
                j = cnt++;
            }
        }
        for (const auto& i : ary) {
            for (const auto& j : i) {
                printf("%d ", j);
            }
            printf("\n");
        }
    }
    {
        // count_if
        // 3の倍数だけカウントする
        std::vector<int> ary{};
        for (int cnt = 1; cnt <= 12; cnt++) {
            ary.emplace_back(cnt);
        }
        auto f = [](int i) -> bool {return(i % 3 == 0); };
        printf("%lld\n", std::count_if(ary.begin(), ary.end(), f));
    }
    {
        std::vector<int> vec{ 40, 10, 20, -10, 30 };
        for (const auto& i : vec) {
            printf("%d ", i);
        }
        printf("\n");
        std::sort(vec.begin(), vec.end(), std::greater<>());    // greater 降順にソートする
        for (const auto& i : vec) {
            printf("%d ", i);
        }
        printf("\n");
        std::sort(vec.begin(), vec.end(), std::less<>());       // less 昇順にソートする
        for (const auto& i : vec) {
            printf("%d ", i);
        }
        printf("\n");
    }
    {
        // int型配列のソート
        int ary[] = { 5, 1, 3, 2, 4 };
        std::sort(std::begin(ary), std::end(ary));  // int ary[]を昇順にソートする
        for (int i = 0; i < std::size(ary); i++) {
            printf("%d ", ary[i]);
        }
        printf("\n");
    }
    {
        // all_of 全ての要素が条件を満たせばtrue、例外があればfalse
        //std::vector<int> ary[] = { 1, 2, 3, 4, 5 };
        int ary[]{ 1, 2, 3, 4, 5 };
        bool b = std::all_of(std::begin(ary), std::end(ary), [](int i) {return i < 10; });
        printf("%s\n", (b) ? "true" : "false");
        b = std::all_of(std::begin(ary), std::end(ary), [](int i) {return i < 5; });
        printf("%s\n", (b) ? "true" : "false");
    }
    {
        // any_of 要素のうち一つでも条件を満たせばtrue、無ければfalse
        //std::vector<int> ary[] = { 1, 2, 3, 4, 5 };
        int ary[]{ 1, 2, 3, 4, 5 };
        bool b = std::any_of(std::begin(ary), std::end(ary), [](int i) {return i == 3; });
        printf("%s\n", (b) ? "true" : "false");
        b = std::any_of(std::begin(ary), std::end(ary), [](int i) {return i == 6; });
        printf("%s\n", (b) ? "true" : "false");
    }
    {
        // none_of 全ての要素の条件が満たせなければtrue、一つでも満たせばfalse
        //std::vector<int> ary[] = { 1, 2, 3, 4, 5 };
        int ary[]{ 1, 2, 3, 4, 5 };
        bool b = std::none_of(std::begin(ary), std::end(ary), [](int i) {return i > 5; });
        printf("%s\n", (b) ? "true" : "false");
        b = std::none_of(std::begin(ary), std::end(ary), [](int i) {return i > 4; });
        printf("%s\n", (b) ? "true" : "false");
    }
    {
        // unoreder_map
        std::unordered_map<int, std::string> um;
        um[0] = "AAA";
        um[1] = "BBB";
        um[2] = "CCC";
        um[3] = "DDD";
        for (const auto& i : um) {
            std::cout << i.first << " " << i.second << std::endl;   // mapの要素を取り出すときはfirst、secondを使う
        }
    }
    {
        // ラムダ式
        auto f = [] {};
        f();
        auto f2 = [] {return 1; };
        printf("%d\n", f2());
        printf("%f\n", []() -> auto {return 2.2f; }());
        std::cout << []() -> auto {return 2.2f; }() << std::endl;
        int i{ 1 };
        printf("%d\n", [i]() {return 1+1; }());
        printf("%d\n", [&i] { return ++i; }());
        printf("%d\n", [i](int j){return i + j; }(1));
        printf("%d\n", [&i](int j) {return ++i + j; }(1));
        std::cout << [] {return "AAAAA"; }() << std::endl;
    }
    {
        // std::deque リングバッファとして使える
        std::deque<int> deq{};
        deq.emplace_back(1);
        deq.emplace_back(2);
        deq.emplace_back(3);
        printf("size %d\n", deq.size());
        for (int cnt = 0; cnt < deq.size(); cnt++) {
            printf("%d\n", deq[cnt]);
        }
        deq.pop_front();
        deq.pop_front();
        deq.emplace_back(4);
        deq.emplace_back(5);
        printf("size %d\n", deq.size());
        for (int cnt = 0; cnt < deq.size(); cnt++) {
            printf("%d\n", deq[cnt]);
        }
    }
}

// インライン名前空間
namespace inlineNameSpace {
    namespace A {
        void funcA() {}
    }
    inline namespace B {
        void funcB() {}
    }
}
// ユーザー定義リテラル
namespace user_defined_literals {
    unsigned long long int operator"" _m(unsigned long long int i) {
        return i;
    }
    unsigned long long int operator"" _km(unsigned long long int i) {
        return i * 1000;
    }
    unsigned long long int operator"" _mm(unsigned long long int i) {
        return i * 1000 * 1000;
    }
}
using namespace user_defined_literals;  // ユーザー定義リテラル

// 委譲コンストラクタ、継承コンストラクタ、delete宣言
class C2103221422 {
public:
    C2103221422(int a, int b, int c) {
        printf("%d = %d * %d * %d\n", a * b * c, a, b, c);
    }
    C2103221422() : C2103221422(1, 1, 1) {}    // 委譲コンストラクタ
    C2103221422(int a) : C2103221422(a, 1, 1) {}    // 委譲コンストラクタ
    C2103221422(int a, int b) : C2103221422(a, b, 1) {}    // 委譲コンストラクタ
    C2103221422(std::vector<int>& v) : C2103221422(v[0], v[1], v[2]) {}    // 委譲コンストラクタ
};
class DeriC2103221422 : public C2103221422 {
public:
    using C2103221422::C2103221422; // 継承コンストラクタ
    DeriC2103221422(int a) = delete;
    DeriC2103221422(std::vector<int>& v) = delete;
};

// alignas コンパイラに対し変数をメモリ上の特定の位置に配置（アライメント）するように要求するキーワード
struct alignasSt{
char	buff[4];
};
struct alignas(8) alignasSt8{
char	buff[4];
};
struct alignas(16) alignasSt16{
char	buff[4];
};
struct alignas(32) alignasSt32{
char	buff[4];
};

// 宣言時に要素数を指定した配列オブジェクトの、定義時の要素数を規定
extern int staticIntAray[10];

void func5() {
    {
        inlineNameSpace::A::funcA();
        //inlineNameSpace::funcA();   // funcAは見えないのでエラー
        inlineNameSpace::funcB();    // インライン名前空間 (inline namespace)は、名前空間内の機能に透過的にアクセスするための機能
    }
    {
        // ユーザー定義リテラル
        unsigned long long int i = 1_mm + 500_km + 700_m;
        printf("%lld\n", i);
    }
    {
        C2103221422 b1{ 3, 3, 3 };
        C2103221422 b2{ 3, 3 };
        C2103221422 b3{ 3 };
        C2103221422 b4{};
        std::vector<int> v{ 4, 4, 4 };
        C2103221422 b5{ v };
        DeriC2103221422 d1{ 3, 3, 3 };    // 継承してるので使用可能
        DeriC2103221422 d2{ 3, 3 };   // 継承してるので使用可能
        //DeriC2103221422 d3(3);  // deleteしてるので使用不可
        DeriC2103221422 d4{};   // 継承してるので使用可能

        //DeriC2103221422 d4();   // ()にすると継承コンストラクタが呼ばれない

        //DeriC2103221422 d5{v};  // deleteしてるので使用不可
    }
    {
		// extern template
		large_class<int> l;
		large_func<int>();
	}
	{
		/*
			マルチスレッドに関連する項目
			
				スレッドローカルストレージ
				ブロックスコープを持つstatic変数初期化のスレッドセーフ化
				[[carries_dependency]]属性
		*/
	}
	{
		// alignas コンパイラに対し変数をメモリ上の特定の位置に配置（アライメント）するように要求するキーワード
		printf("%d\n", static_cast<int>(sizeof(alignasSt)));
		printf("%d\n", static_cast<int>(sizeof(alignasSt8)));
		printf("%d\n", static_cast<int>(sizeof(alignasSt16)));
		printf("%d\n", static_cast<int>(sizeof(alignasSt32)));
	}
	{
		// 宣言時に要素数を指定した配列オブジェクトの、定義時の要素数を規定
		//int staticIntAray[];	// error C2133
		//printf("%d\n", static_cast<int>(sizeof(staticIntAray)));
	}
	{
		// sizeof演算子にクラスの非静的メンバを、オブジェクトを作らずに指定できるようにする
		printf("size: %d\n", static_cast<int>(sizeof(alignasSt::buff)));
		printf("size: %d\n", static_cast<int>(sizeof(alignasSt32::buff)));
	}
	{
    	// std::next
    	// std::prev
   	    std::vector<int> stVec{ 1, 2, 3, 4, 5 };
    	decltype(stVec)::iterator it = std::next(stVec.begin());    // 1つ進む 1→2
    	printf("next %d\n", *it);
    	it = std::next(stVec.begin(), 3);   // 3つ進む 1→4
    	printf("next %d\n", *it);
    	it = std::prev(stVec.end());        // 1つ戻る 範囲外→5   最後尾の値を取得したいときは、これを使う
    	printf("prev %d\n", *it);
    	it = std::prev(stVec.end(), 2);     // 2つ戻る 範囲外→4
    	printf("prev %d\n", *it);
    	printf("begin %d\n", *(stVec.begin())); // 最初の値
    	//printf("end %d\n", *(stVec.end()));   // 範囲外なので異常終了する
	}
	{
		// std::begin() std::end()
		int ary[] = {5, 3, 6, 1, 9, 7, 2};
		std::for_each(std::begin(ary), std::end(ary), [](int x){printf("%d ", x);});
		printf("\n");
	}
}

class memberInitTestClass {
private:
    int i = 100;    // 非静的メンバ変数の初期化
    int ii{ 200 };  // 非静的メンバ変数の初期化
    std::string st{"AAA"};  // 非静的メンバ変数の初期化
};
int main()
{
    func();
    lambdaExpressions();
    unionConfirm();
    returnFunc();
    func2();
    old_func();
    makeUniquePtrFunc();
    uniquePtr();
    uniquePtr2();
    func3();
    func4();
    func5();
    
    sub_func();

    return 0;
}
