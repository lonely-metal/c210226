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

// �錾���ɗv�f�����w�肵���z��I�u�W�F�N�g�́A��`���̗v�f�����K��
static int staticIntAray[10];

#endif // _C210226
