#include "Danmaku.h"

bool Danmaku::init()
{
#define DanmakuSize 0.05

	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());

		bullet = Sprite::create("sprites/danmaku.png");
		SETSIZE(bullet, DanmakuSize);
		this->addChild(bullet);

		bRet = true;
	} while (0);
	return bRet;
}

void Danmaku::danmakuAttack(Point p)
{
	bullet->setPosition(p);
}

void Danmaku::run2P(Point& pos, int d, int speed)
{
	ActionInterval* run = MoveBy::create(d, pos);
	RepeatForever* runf = RepeatForever::create(run);
	Speed* runs = Speed::create(runf, speed*10);
	bullet->runAction(runs);
	int angle = atan2(pos.y, -pos.x)*180/3.14;
	bullet->setRotation(angle);
}

bool Danmaku::checkCollision(Rect playerRect)
{
	return bullet->getBoundingBox().intersectsRect(playerRect);
}

bool Danmaku::checkOut()
{
	Rect r = bullet->getBoundingBox();
	if (r.getMaxX() < 0 || r.getMinY() > visibleSize.height || r.getMaxY() < 0 || r.getMinX() > visibleSize.width)
		return true;
	return false;
}