//#pragma once
#ifndef _C210226
#define _C210226

class inlineValueTest {
public:
	static inline int i;	// �C�����C���ϐ�
};

void inlineTestFunc(inlineValueTest i);
void sub_func();

// extern template
template <class T>
class large_class{};
template <class T>
void large_func(){}

#endif // _C210226
