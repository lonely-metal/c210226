//#pragma once
#ifndef _C210226
#define _C210226

class inlineValueTest {
public:
	static inline int i;	// インライン変数
};

void inlineTestFunc(inlineValueTest i);
void sub_func();

// extern template
template <class T>
class large_class{};
template <class T>
void large_func(){}

// 宣言時に要素数を指定した配列オブジェクトの、定義時の要素数を規定
static int staticIntAray[10];

#endif // _C210226
