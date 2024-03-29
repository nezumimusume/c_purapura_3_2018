// Lesson2.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Player.h" //Playerクラスを使いたいので、ヘッダーファイルをインクルードする。
#include "Enemy.h"	//Enemyクラスを使いたいので、ヘッダーファイルをインクルードする。

//マップの高さ。
const int MAP_HEIGHT = 16;
//マップの幅。
const int MAP_WIDTH = 16;

//フレームバッファみたいなもの・・・
static char sFrameBuffer[MAP_HEIGHT][MAP_WIDTH];
//ゲームオーバーフラグ。
bool g_gameOverFlag = false;



////////////////////////////////////////
//フレームバッファに文字を描画。
////////////////////////////////////////
void DrawMoji(int posX, int posY, char moji)
{
	//フレームバッファの幅と高さを超えていないかチェック。
	if (posX < MAP_WIDTH && posY < MAP_HEIGHT) {
		sFrameBuffer[posY][posX] = moji;
	}
}
////////////////////////////////////////
//1フレームの最初に呼ばれる関数。
////////////////////////////////////////
void BeginFrame()
{
	//フレームバッファをクリア。
	memset(sFrameBuffer, 0, sizeof(sFrameBuffer));
}
////////////////////////////////////////
//1フレームの終わりに呼ばれる関数。
////////////////////////////////////////
void EndFrame()
{
	//フレームバッファの内容を画面に表示する。
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			std::cout << sFrameBuffer[i][j];
		}
		std::cout << "\n";
	}

	//100ミリ秒眠る。
	Sleep(100);

	//標準出力コンソールのハンドルを取得。
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = 0;
	pos.Y = 0;
	//標準コンソールのカーソルを0行目、0列に戻す。
	SetConsoleCursorPosition(hCons, pos);
	
}

////////////////////////////////////////
// メイン関数。
////////////////////////////////////////
int main()
{
	//プレイヤーの初期化、。
	g_player.posX = 5;
	g_player.posY = 5;
	//エネミーのインスタンスを10個用意する。
	Enemy enemy[10];
	//初期座標を決めていく。
	enemy[0].posX = 2;
	enemy[0].posY = 1;

	enemy[1].posX = 3;
	enemy[1].posY = 4;

	enemy[2].posX = 3;
	enemy[2].posY = 6;

	enemy[3].posX = 6;
	enemy[3].posY = 3;

	enemy[4].posX = 2;
	enemy[4].posY = 7;

	enemy[5].posX = 9;
	enemy[5].posY = 9;

	enemy[6].posX = 10;
	enemy[6].posY = 14;

	enemy[7].posX = 8;
	enemy[7].posY = 6;

	enemy[8].posX = 11;
	enemy[8].posY = 4;

	enemy[9].posX = 2;
	enemy[9].posY = 15;

	//ゲームループ。
	while (true) {
		//1フレームの開始。
		BeginFrame();
		
		if (g_gameOverFlag == false) {
			//プレイヤーの移動処理を実行。
			g_player.Move();
			//プレイヤーの描画処理を実行。
			g_player.Draw();

			//エネミーの移動処理を実行。
			for (int i = 0; i < 10; i++) {
				enemy[i].Move();
			}
			//エネミーの描画処理を実行。
			for (int i = 0; i < 10; i++) {
				enemy[i].Draw();
			}
		}
		else if (g_gameOverFlag == true) {
			//ゲームオーバー。
			DrawMoji(0, 4, 'G');
			DrawMoji(1, 4, 'A');
			DrawMoji(2, 4, 'M');
			DrawMoji(3, 4, 'E');
			DrawMoji(4, 4, ' ');
			DrawMoji(5, 4, 'O');
			DrawMoji(6, 4, 'V');
			DrawMoji(7, 4, 'E');
			DrawMoji(8, 4, 'R');
		}
		//フレームの終わり。
		EndFrame();
	}
    return 0;
}

