#include "PlayerLayer.h"

using namespace CR;

#define STAND_ANIMATE 1
#define UPWARD_ANIMATE 2
#define DOWNWARD_ANIMATE 3

bool PlayerLayer::init()
{
#define PlayerSize 0.12
#define PlayerPositionX visibleSize.width*1/4
#define PlayerPositionY visibleSize.height*3/6
#define PositionPointSize 0.04
#define HealthSizeX 0.5
#define HealthSizeY 0.032
#define HealthPositionY visibleSize.height

	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		health = 1;
		healthMax = 1;
		createPlayer("sprites/player.png");
		createHealth("selfhealth.png");

		Controller::setControler(Sprite::create("controller/round.png"), Sprite::create("controller/ball.png"), 0.1f, 0.025f);
		Controller::setTouchRect(Rect(0, 0, visibleSize.width / 2, visibleSize.height));
		Controller::setSpeedMax(12);
		Controller::set8DirectionMode(false);
		Controller::set4DirectionMode(false);

		this->scheduleUpdate();

		bRet = true;
	} while (0);
	return bRet;
}

void PlayerLayer::createPlayer(string filename)
{
	Player = Sprite::create(filename);
	Player->setPosition(Point(origin.x + PlayerPositionX, origin.y + PlayerPositionY));
	SETSIZE(Player, PlayerSize);
	this->addChild(Player);
}

void PlayerLayer::createHealth(string filename)
{
	Health = Sprite::createWithSpriteFrameName(filename);
	Health->setAnchorPoint(Point(0, 1));
	SETSIZE(Health, HealthSizeY);
	healthLength = visibleSize.width / Health->getContentSize().width * HealthSizeX;
	Health->setScaleX(healthLength * health / healthMax);
	Health->setPosition(Point(origin.x, origin.y + HealthPositionY));
	this->addChild(Health, -1);
}

bool PlayerLayer::changeHealth(int delta)
{
	bool negative = false;
	health += delta;
	if (health < 0)
	{
		health = 0;
		negative = true;
	}
	if (health > healthMax)
	{
		health = healthMax;
	}
	Health->setScaleX(healthLength * health / healthMax); 
	return negative;
}

void PlayerLayer::setHealth(int health)
{
	this->health = health;
}

void PlayerLayer::setHealthMax(int healthMax)
{
	this->healthMax = healthMax;
}

int PlayerLayer::getHealth()
{
	return health;
}

Point PlayerLayer::getPlayerPosition()
{
	return Player->getPosition();
}

Rect PlayerLayer::getPlayerRect()
{
	return Player->getBoundingBox();
}

void PlayerLayer::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->onTouchBegan = CC_CALLBACK_2(PlayerLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerLayer::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(PlayerLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool PlayerLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	Controller::onTouchBegan(touch, unused_event);

	return true;
}

void PlayerLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	Controller::onTouchMoved(touch, unused_event);
}

void PlayerLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	Controller::onTouchEnded(touch, unused_event);
}

void PlayerLayer::update(float dt)
{
	Player->setPositionX(Player->getPositionX() + Controller::getSpeedX());
	Player->setPositionY(Player->getPositionY() + Controller::getSpeedY());

	Point position = Player->getPosition();

	if (position.x < 0)
	{
		Player->setPositionX(0);
	}
	else if (position.x >visibleSize.width)
	{
		Player->setPositionX(visibleSize.width);
	}
	if (position.y < 0)
	{
		Player->setPositionY(0);
	}
	else if (position.y > visibleSize.height)
	{
		Player->setPositionY(visibleSize.height);
	}
}
