#pragma once

#include "Global.h"

class Trash : public Node
{
public:
	CREATE_FUNC(Trash);
	void trashAttack(float y);
	bool checkOut();
	void move();
	void setSpeed(float s);
	Rect getBox();
	bool checkCollision(Rect playerRect);

protected:
	bool init();
	/*//////////////////////////////////////////////////*/
	KEYBOARD_FUNCTION;
	/*//////////////////////////////////////////////////*/

	Sprite* trash;
	float speed;
};