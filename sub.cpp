#include "c210226.h"
#include <cstdio>

void inlineTestFunc(inlineValueTest i) {
	i.i = 999;
}

// extern template
extern template class large_class<int>;
extern template void large_func<int>();

// 宣言時に要素数を指定した配列オブジェクトの、定義時の要素数を規定
//extern int staticIntAray[5];	// 添字の値変えたら、error C2369
extern int staticIntAray[10];

void sub_func(){
   	{
		printf("___sub_func()___\n");
		
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
	{
		// 宣言時に要素数を指定した配列オブジェクトの、定義時の要素数を規定
		//int staticIntAray[];	// error C2133
		//printf("%d\n", static_cast<int>(sizeof(staticIntAray)));
	}
	{
	}
}
