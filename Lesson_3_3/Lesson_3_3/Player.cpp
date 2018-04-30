#include "stdafx.h"
#include "Player.h"

//プレイヤーのインスタンス。
Player g_player;

Player::Player()
{
}



Player::~Player()
{
}

void Player::Draw()
{
	//プレイヤーをフレームバッファに描画。
	DrawMoji(posX, posY, 'P');

}
void Player::Move()
{
	//プレイヤーの移動処理。
	if (GetAsyncKeyState(VK_UP)) {
		posY--;
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		posY++;
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		posX++;
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		posX--;
	}
}

