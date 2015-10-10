#pragma once

#include "Global.h"

class Danmaku : public Node
{
public:
	CREATE_FUNC(Danmaku);
	void danmakuAttack(Point p);
	void run2P(Point& pos, int d, int speed);
	bool checkCollision(Rect playerRect);
	bool checkOut();
	void remove();

protected:
	bool init();
	/*//////////////////////////////////////////////////*/
	KEYBOARD_FUNCTION;
	/*//////////////////////////////////////////////////*/

	Sprite* bullet;
};

