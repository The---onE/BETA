#include "Bullet.h"

bool Bullet::init()
{
#define BulletSize 0.05

	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());

		bullet = Sprite::create("sprites/attatk.png");
		SETSIZE(bullet, BulletSize);
		this->addChild(bullet);

		bRet = true;
	} while (0);
	return bRet;
}

void Bullet::bulletAttack(Point p)
{
	bullet->setPosition(p);
}

bool Bullet::checkCollision(Rect enemyRect)
{
	return bullet->getBoundingBox().intersectsRect(enemyRect);
}

bool Bullet::checkOut()
{
	return bullet->getBoundingBox().getMinX() > visibleSize.width;
}

void Bullet::move()
{
	bullet->setPositionX(bullet->getPositionX() + speed);
}

void Bullet::setSpeed(float s)
{
	speed = s;
}