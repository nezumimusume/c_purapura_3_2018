// stl_vector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>	//これをインクルードすることでSTLのvectorが使えるようになる。
#include <algorithm>

bool IsCompare(int value)
{
	if (value <= 20) {
		//20より小さかったら削除！
		return true;
	}
	return false;
}
int main()
{
	////////////////////////////////////////////////////////////////////
	//Chapter 1 要素の追加。
	////////////////////////////////////////////////////////////////////
	std::vector<int>  value;	//可変長配列。要素を動的に変更することができる。
	value.push_back(10);		//要素の追加。
	value.push_back(20);		//
	value.push_back(30);

	////////////////////////////////////////////////////////////////////
	//Chapter 2 要素へのアクセス。
	////////////////////////////////////////////////////////////////////

	//2.1	for文を使ってSTLの要素にアクセスする。
	//
	//配列と同じように扱える。
	//std::vectorにはsizeというメンバ変数がある。
	//これは現在の要素数を返すメンバ変数。
	//18行目の時点だといくつを返す？？？？
	for (int i = 0; i < value.size(); i++)
	{
		printf("%d\n", value[i]);
	}
	//2.1	イテレーターを使ってSTLの要素にアクセスする。
	//
	//std::vectorには要素にアクセスするためにイテレータ(反復子)というものも使える。
	//こんな感じ。
	std::vector<int>::iterator it;
	//ポインタのような感じで使える。
	for ( it = value.begin();		//動的配列の最初の要素から初めて、
		it != value.end();			//終端になるまでループを回す。
		it++
	) {
		printf("%d\n", *it);		//まるでポインタのように扱える。
	}
	/*
		こんなコードと同じ。
		int a[10];
		int* p ;
		for( p = a;			//配列の先頭アドレスから初めて
		　 p != &a[9]		//配列の終端になるまでループを回す。
		   p++
		)
		{
			printf("%d\n", *it);		//まるでポインタのように扱える。
		}
	 */
	//2.2	型推論とforeachを使ってアクセスする。
	//
	//C++11というC++の拡張仕様で追加された機能。
	for (auto v : value) {
		printf("%d\n", v);
	}
	////////////////////////////////////////////////////////////////////
	//Chapter3 要素の削除。
	//ここからちょっと難しい
	//ここまでの内容でもstd::vectorは使えるので、この先は理解できなくてもいいので使って覚えよう！
	////////////////////////////////////////////////////////////////////
	//動的配列は要素を削除することができる。
	//要素の削除はstd::vectorのメンバ変数のeraseを使えば実行できる。
	//eraseに削除したイテレータを渡せばいい。
	//なので例えば10を削除したい場合はこんなコードを書けばいい？
#if 0
	for (
		it = value.begin();
		it != value.end();
		it++				//残念ながらここでクラッシュが発生する。なぜ？
	) {
		if (*it == 10) {
			value.erase(it);		
		}
	}
#else
	//eraseされたイテレータは無効になってしまう。
	//無効になったイテレータに対してit++を実行しているためクラッシュが発生する。
	//じゃぁどうするの？
	//こうする。
	it = value.begin();
	while(it != value.end()) {
		if (*it == 10) {
			it = value.erase(it);		//erase関数は削除されたイテレータの次を返してくるので、eraseの戻り値を使う。
		}
		else {
			it++;						//それ以外は次へ。
		}
	}
#endif
	////////////////////////////////////////////////////////////////////
	//ここからさらに難しい。
	////////////////////////////////////////////////////////////////////
	//この削除の仕方はまだろっこしい。
	//さらに発展的なことを勉強したい人へ・・・・
	//要素の削除はerase-removeイディオムを使おう！！！
	//std::removeは実は削除はしない。条件にマッチする要素を末尾に移動させるだけ。
	//ホントに削除するためにはeraseを使う必要がある。
	//これがerase-removeイディオム。
	value.erase(
		std::remove(value.begin(), value.end(), 3),		
		value.end()
	);
	
	
	//特殊な条件で削除したい場合はstd_remove_ifを使う。
#if 0	
	//関数ポインタを使う版。
	value.erase(
		std::remove_if(value.begin(), value.end(), IsCompare),
		value.end()
	);
#else	
	//ラムダ式を使う版。先進的なコード。
	//関数ポインタ版は、関数の本体が遠くにあるので、コードが読みづらい。
	//あと、この手の関数は沢山出来るので、名前を考えるのもめんどくさい。
	//そうだ！匿名関数を使おう！！！
	auto func = [](int value)->bool {	//匿名関数。
		if (value <= 20) {
			//20より小さかったら削除！
			return true;
		}
		return false;
	};

	value.erase(
		std::remove_if(value.begin(), value.end(), func),
		value.end()
	);
#endif
	printf("----------------------------------\n");
	for (auto v : value) {
		printf("%d\n", v);
	}
    return 0;
}

