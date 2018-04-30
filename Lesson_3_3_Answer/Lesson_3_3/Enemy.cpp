#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}
void Enemy::Move()
{
	//X座標上で移動させる。
	posX += moveDir;
	//移動方向を反転。
	moveDir *= -1;
}
void Enemy::Draw()
{
	DrawMoji(posX, posY, 'E');
	if (g_player.GetPosX() == posX
		&& g_player.GetPosY() == posY
	) {
		//エネミーとプレイヤーが同じ座標に来たのでゲームオーバーにする。
		g_gameOverFlag = true;
	}
}

