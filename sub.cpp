#include "c210226.h"
#include <cstdio>

void inlineTestFunc(inlineValueTest i) {
	i.i = 999;
}

// extern template
extern template class large_class<int>;
extern template void large_func<int>();

// �錾���ɗv�f�����w�肵���z��I�u�W�F�N�g�́A��`���̗v�f�����K��
//extern int staticIntAray[5];	// �Y���̒l�ς�����Aerror C2369
extern int staticIntAray[10];

void sub_func(){
   	{
		printf("___sub_func()___\n");
		
		// extern template
		large_class<int> l;
		large_func<int>();
		/*
			extern template�錾���Ȃ��ꍇ�̃t�@�C���T�C�Y
				sub.obj		  1,294
				c210226.exe	431,616

			extern template�錾�����ꍇ�̃t�@�C���T�C�Y
				sub.obj		  1,207
				c210226.exe	431,616
				
			obj�̃T�C�Y�͏������邯��exe�̃T�C�Y������
			�����Ǝg���ꏊ�A�I�u�W�F�N�g�̃T�C�Y��������΁A�����o�Ă���̂��H
		*/
	}
	{
		// �錾���ɗv�f�����w�肵���z��I�u�W�F�N�g�́A��`���̗v�f�����K��
		//int staticIntAray[];	// error C2133
		//printf("%d\n", static_cast<int>(sizeof(staticIntAray)));
	}
	{
	}
}
