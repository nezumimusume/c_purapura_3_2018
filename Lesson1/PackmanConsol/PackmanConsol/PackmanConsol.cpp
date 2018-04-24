// PackmanConsol.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>

//マップの高さ。
const int MAP_HEIGHT = 15;
//マップの幅。
const int MAP_WIDTH = 15;

//マップの定義。1は壁。0は餌。
static int sMap[MAP_HEIGHT][MAP_WIDTH] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

//フレームバッファ・・・のようなもの。
static char sFrameBuffer[MAP_HEIGHT][MAP_WIDTH];

void EndFrame()
{
	Sleep(100);	//100ミリ秒眠る。
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = 0;
	pos.Y = 0;

	SetConsoleCursorPosition(hCons, pos);
}

/*!
 *@brief	プレイヤークラス。
 */
class CPlayer {
private:
	int m_posX;			//!<x座標。
	int m_posY;			//!<y座標。
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	CPlayer()
	{
		//初期化を行う。
		m_posX = 0;
		m_posY = 0;
	}
	/*!
	 *@brief	デストラクタ。
	 */
	~CPlayer()
	{

	}
	/*!
	*@brief	プレイヤーの描画処理。
	*/
	void Draw()
	{
		//フレームバッファにドロー。
		sFrameBuffer[m_posY][m_posX] = 'P';
	}
	/*!
	 *@brief	更新処理。
	 */
	void Update()
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			m_posY--;
			if (m_posY < 0) {
				m_posY = 0;
			}
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			m_posX--;
			if (m_posX < 0) {
				m_posX = 0;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			m_posY++;
			if (m_posY > MAP_HEIGHT - 1) {
				m_posY = MAP_HEIGHT - 1;
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			m_posX++;
			if (m_posX > MAP_WIDTH - 1) {
				m_posX = MAP_WIDTH - 1;
			}
		}
	}
	/*!
	 *@brief	X座標を取得。
	 */
	int GetPositionX()
	{
		return m_posX;
	}
	/*!
	 *@brief	Y座標を取得。
	 */
	int GetPositionY()
	{
		return m_posY;
	}
	/*!
	 *@brief	座標を設定。
	 *@param	x		x座標。
	 *@param	y		y座標。
	 */
	void SetPosition(int x, int y)
	{
		m_posX = x;
		m_posY = y;
	}
};
CPlayer g_player;

/*!
*@brief	食べ物クラス。
*/
class CFood {
private:
	int m_posX;		//!<x座標。
	int m_posY;		//!<y座標
	bool m_isDead;	//!<死亡フラグ。
public:
	/*!
	*@brief	コンストラクタ。
	*/
	CFood() :
		m_isDead(false)
	{
		m_posX = 0;
		m_posY = 0;
	}
	/*!
	*@brief	壁の描画処理。
	*/
	void Draw()
	{
		if (!m_isDead) {
			//フレームバッファにドロー。
			sFrameBuffer[m_posY][m_posX] = 'F';
		}
	}
	/*!
	*@brief	座標を設定。
	*/
	void SetPosition(int x, int y)
	{
		m_posX = x;
		m_posY = y;
	}
	/*!
	*@brief	更新処理。
	*/
	void Update()
	{
		//プレイヤーと触れたら食べ物が消えるようにしてみよう・・・
		//プレイヤーはg_playerでアクセスできる。
		//プレイヤーとCFoodの座標が同じになった時に、消えるようにすればいいはず。
		//プレイヤーの座標はg_player.GetPositionX()とg_player.GetPositionY()で取得できる。
		//例えばプレイヤーのX座標が欲しいならこんな感じ。
		//int pos_x = g_player.GetPositionX();
	}
};
/*!
*@brief	壁クラス。
*/
class CWall {
private:
	int	m_posX;		//!<x座標。
	int m_posY;		//!<y座標
public:
	/*!
	*@brief	コンストラクタ。
	*/
	CWall()
	{
		m_posX = 0;
		m_posY = 0;
	}
	/*!
	*@brief	壁の描画処理。
	*/
	void Draw()
	{
		//フレームバッファにドロー。
		sFrameBuffer[m_posY][m_posX] = 'W';
	}
	/*!
	*@brief	座標を設定。
	*/
	void SetPosition(int x, int y)
	{
		m_posX = x;
		m_posY = y;
	}
};

/*!
 *@brief	メイン関数。
 */
int main()
{
	//プレイヤーの初期位置を決定。
	g_player.SetPosition(7, 7);
	//壁
	int numWall = 0;	//壁の数。
	CWall walls[MAP_HEIGHT*MAP_WIDTH];
	//食べ物
	int numFood = 0;
	CFood foods[MAP_HEIGHT*MAP_WIDTH];
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (sMap[i][j] == 1) {
				//壁。
				walls[numWall].SetPosition(j, i);
				//壁を一つ作ったのでカウントアップ。
				numWall++;
			}
			else if (sMap[i][j] == 0) {
				//食べ物
				foods[numFood].SetPosition(j, i);
				//食べ物を一つ作ったのでカウントアップ。
				numFood++;
			}
		}
	}
	//ゲームループ。
	while (true) {
		//フレームバッファをクリア。
		memset(sFrameBuffer, 0, sizeof(sFrameBuffer));
		//プレイヤーの移動処理。
		g_player.Update();
		//食べ物の更新処理。
		for (int i = 0; i < numFood; i++) {
			foods[i].Update();
		}
		//食べ物の描画処理。
		for (int i = 0; i < numFood; i++) {
			foods[i].Draw();
		}
		//壁の描画処理。
		for (int i = 0; i < numWall; i++) {
			walls[i].Draw();
		}
		//プレーヤーの描画処理。
		g_player.Draw();
		//フレームバッファの内容を画面に表示する。
		for (int i = 0; i < MAP_HEIGHT; i++) {
			for (int j = 0; j < MAP_WIDTH; j++) {
				std::cout << sFrameBuffer[i][j];
			}
			std::cout << "\n";
		}
		EndFrame();	//フレームの最後に呼んでね。おまじない。
	}
    return 0;
}

