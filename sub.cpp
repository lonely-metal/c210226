#include "c210226.h"

void inlineTestFunc(inlineValueTest i) {
	i.i = 999;
}
// extern template
extern template class large_class<int>;
extern template void large_func<int>();

void sub_func(){
   	{
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
}