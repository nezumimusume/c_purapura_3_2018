#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Move();
	void Draw();
	void SetPos(int x, int y) 
	{
		posX = x;
		posY = y;
	}
private:
	int posX = 0;		//エネミーのX座標。
	int posY = 0;		//エネミーのY座標。
	int moveDir = 1;	//エネミーの移動方向。
};

