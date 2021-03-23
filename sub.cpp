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
			extern template宣言しない場合のファイルサイズ
				sub.obj		  1,294
				c210226.exe	431,616

			extern template宣言した場合のファイルサイズ
				sub.obj		  1,207
				c210226.exe	431,616
				
			objのサイズは少し減るけどexeのサイズが同じ
			もっと使う場所、オブジェクトのサイズが増えれば、差が出てくるのか？
		*/
	}
}