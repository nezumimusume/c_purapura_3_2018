#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Move();
	void Draw();
	int posX = 0;		//エネミーのX座標。
	int posY = 0;		//エネミーのY座標。
	int moveDir = 1;	//エネミーの移動方向。
};

