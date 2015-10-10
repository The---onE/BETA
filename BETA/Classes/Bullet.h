#pragma once

#include "Global.h"

class Bullet : public Node
{
public:
	CREATE_FUNC(Bullet);
	void bulletAttack(Point p);
	bool checkCollision(Rect enemyRect);
	bool checkOut();
	void move();
	void setSpeed(float s);

protected:
	bool init();
	/*//////////////////////////////////////////////////*/
	KEYBOARD_FUNCTION;
	/*//////////////////////////////////////////////////*/

	Sprite* bullet;
	float speed;
};