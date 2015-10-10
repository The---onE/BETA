#include "Trash.h"

bool Trash::init()
{
#define TrashSize 0.12

	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());

		trash = Sprite::create("sprites/trash.png");
		trash->setAnchorPoint(Point(0, 0.5));
		SETSIZE(trash, TrashSize);
		this->addChild(trash);

		bRet = true;
	} while (0);
	return bRet;
}

void Trash::trashAttack(float y)
{
	trash->setPosition(Point(visibleSize.width, y));
}

bool Trash::checkOut()
{
	return trash->getBoundingBox().getMaxX() < 0;
}

void Trash::move()
{
	trash->setPositionX(trash->getPositionX() - speed);
}

void Trash::setSpeed(float s)
{
	speed = s;
}

Rect Trash::getBox()
{
	return trash->getBoundingBox();
}

bool Trash::checkCollision(Rect playerRect)
{
	return trash->getBoundingBox().intersectsRect(playerRect);
}