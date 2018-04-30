#pragma once
class Player
{
public:
	Player();
	~Player();
	void Draw();
	void Move();
	int GetPosX()
	{
		return posX;
	}
	int GetPosY()
	{
		return posY;
	}
	void SetPos(int x, int y) 
	{
		posX = x;
		posY = y;
	}
private:
	int posX = 0;
	int posY = 0;
};
//プレイヤーのインスタンスのextern宣言。
//extern宣言は、定義はどこかにあるから、それを使いなさいと、
//コンパイラに教えるもの。定義ではないので注意！
//今回は定義はPlayer.cppに記述しています。
extern Player g_player;

