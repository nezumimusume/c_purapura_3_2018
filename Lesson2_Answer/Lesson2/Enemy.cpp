#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}
void Enemy::Move()
{
	//XÀ•Wã‚ÅˆÚ“®‚³‚¹‚éB
	posX += moveDir;
	//ˆÚ“®•ûŒü‚ğ”½“]B
	moveDir *= -1;
}
void Enemy::Draw()
{
	DrawMoji(posX, posY, 'E');
}

