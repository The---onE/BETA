#include "GameScene.h"
#include "State/StateList.h"

bool GameScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Scene::init());

		createQuitButton("QuitNormal.png", "QuitSelected.png");
		
		stateMachine = StateMachine::createWithGameScene(this);
		stateMachine->changeState(StartState::create(this));

		score = 0;
		bossFlag = false;

		srand(time(0));
		this->scheduleUpdate();

		//auto rootNode = CSLoader::createNode("MainScene.csb");
		//addChild(rootNode);

		bRet = true;
	} while (0);
	return bRet;
}

void GameScene::initDialog()
{
	bg = BackGroundLayer::create();
	this->addChild(bg, -1000);
	dialog = DialogLayer::create();
	this->addChild(dialog, 1000);
}

void GameScene::removeDialog()
{
	this->removeChild(dialog);
}

void GameScene::initBackGround()
{
	bg = BackGroundLayer::create();
	this->addChild(bg, -1000);
}

void GameScene::setTrashSpeed(float s)
{
	bg->setSpeed(s);
	trashSpeed = s;
}

void GameScene::setBulletSpeed(float s)
{
	bulletSpeed = s;
}

void GameScene::initTrash()
{
	player = PlayerLayer::create();
	player->setHealthMax(100);
	player->setHealth(100);
	this->addChild(player);
}

void GameScene::attack()
{
	Bullet* b = Bullet::create();
	b->bulletAttack(player->getPlayerPosition());
	b->setSpeed(bulletSpeed);
	this->addChild(b);
	bullets.pushBack(b);
}

void GameScene::checkBullet()
{
	for (int i = bullets.size() - 1; i >= 0; --i)
	{
		Bullet* bullet = bullets.at(i);
		bullet->move();
		if (bullet->checkOut())
		{
			bullets.eraseObject(bullet);
			this->removeChild(bullet);
			break;
 		}
		if (bossFlag)
		{
			if (bullet->checkCollision(enemy->getEnemyRect()))
			{
				bullets.eraseObject(bullet);
				this->removeChild(bullet);
				enemy->changeHealth(-10);
				if (effectFlag)
					SimpleAudioEngine::getInstance()->playEffect("musics/hit.wav");
				break;
			}
		}
		for (int j = trashs.size() - 1; j >= 0; --j)
		{
			Trash* trash = trashs.at(j);
			if (bullet->checkCollision(trash->getBox()))
			{
				score += 1;
				bullets.eraseObject(bullet);
				this->removeChild(bullet);
				trashs.eraseObject(trash);
				this->removeChild(trash);
				if (effectFlag)
					SimpleAudioEngine::getInstance()->playEffect("musics/hit.wav");
				break;
			}
		}
	}
}

void GameScene::trashAttack()
{
	Trash* t = Trash::create();
	t->trashAttack((rand_0_1()*0.8+0.1)*visibleSize.height);
	t->setSpeed(trashSpeed);
	this->addChild(t);
	trashs.pushBack(t);
}

void GameScene::checkTrash()
{
	for (int i = trashs.size() - 1; i >= 0; --i)
	{
		Trash* trash = trashs.at(i);
		trash->move();
		if (trash->checkOut())
		{
			trashs.eraseObject(trash);
			this->removeChild(trash);
			player->changeHealth(-20);
			if (effectFlag)
				SimpleAudioEngine::getInstance()->playEffect("musics/hurt.wav");
			break;
		}
		if (trash->checkCollision(player->getPlayerRect()))
		{
			trashs.eraseObject(trash);
			this->removeChild(trash);
			player->changeHealth(-20);
			if (effectFlag)
				SimpleAudioEngine::getInstance()->playEffect("musics/hurt.wav");
			break;
		}
	}
}

int GameScene::getScore()
{
	return score;
}

void GameScene::initBoss()
{
	enemy = EnemyLayer::create();
	this->addChild(enemy);
	enemy->setHealthMax(100);
	enemy->setHealth(100);
	bossFlag = true;
}

void GameScene::danmakuAttack(int num, int angelDeg, int speed)
{
	P2P(player->getPlayerPosition(), enemy->getEnemyPosition(), num, angelDeg, speed);
}

void GameScene::P2P(Point Aim, Point Source, int num, int angelDeg, int speed)
{
	Point Temp;
	float angelRad = CC_DEGREES_TO_RADIANS(angelDeg)/num;
	int d = Aim.getDistance(Source);
	float halfangle = angelRad / 2;
	if (num % 2 == 1)
	{
		halfangle = 0;
		Point Temp = Point(Aim.x - Source.x, Aim.y - Source.y);
		createDanmaku("sprites/danmaku.png", Source, Temp, d, speed);
	}
	for (int i = 1; i <= (num / 2); i++)
	{
		float angel = angelRad * i - halfangle;
		int x = (Aim.x - Source.x)*cos(angel) - (Aim.y - Source.y)*sin(angel);
		int y = (Aim.y - Source.y)*cos(angel) + (Aim.x - Source.x)*sin(angel);
		Temp = Point(x, y);
		createDanmaku("sprites/danmaku.png", Source, Temp, d, speed);

		angel = -angelRad * i + halfangle;
		x = (Aim.x - Source.x)*cos(angel) - (Aim.y - Source.y)*sin(angel);
		y = (Aim.y - Source.y)*cos(angel) + (Aim.x - Source.x)*sin(angel);
		Temp = Point(x, y);
		createDanmaku("sprites/danmaku.png", Source, Temp, d, speed);
	}
}

void GameScene::createDanmaku(string filename, Point& pos, Point& aim, int dis, int speed)
{
	Danmaku* d = Danmaku::create();
	d->danmakuAttack(pos);
	d->run2P(aim, dis, speed);
	this->addChild(d);
	danmakus.pushBack(d);
}

void GameScene::checkDanmaku()
{
	for (int i = danmakus.size() - 1; i >= 0; --i)
	{
		Danmaku* danmaku = danmakus.at(i);
		if (danmaku->checkOut())
		{
			danmakus.eraseObject(danmaku);
			this->removeChild(danmaku);
			break;
		}
		if (danmaku->checkCollision(player->getPlayerRect()))
		{
			danmakus.eraseObject(danmaku);
			this->removeChild(danmaku);
			player->changeHealth(-20);
			if (effectFlag)
				SimpleAudioEngine::getInstance()->playEffect("musics/hurt.wav");
			break;
		}
	}
}

bool GameScene::checkLose()
{
	return player->getHealth() <= 0;
}

void GameScene::lose()
{
	setBulletSpeed(0);
	setTrashSpeed(0);

	this->removeChild(player);

	Sprite* s = Sprite::create("sprites/lose.png");
	s->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	SETSIZE(s, 0.3);
	this->addChild(s);
}

bool GameScene::checkWin()
{
	if (!bossFlag)
		return false;
	return enemy->getHealth() <= 0;
}

void GameScene::win()
{
	setBulletSpeed(0);
	setTrashSpeed(0);

	this->removeChild(enemy);
	for (int i = danmakus.size() - 1; i >= 0; --i)
	{
		Danmaku* danmaku = danmakus.at(i);
		danmakus.eraseObject(danmaku);
		this->removeChild(danmaku);
	}

	Sprite* s = Sprite::create("sprites/win.png");
	s->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	SETSIZE(s, 0.3);
	this->addChild(s);
}

void GameScene::setEffectFlag(bool flag)
{
	effectFlag = flag;
}

StateMachine* GameScene::getStateMachine()
{
	return stateMachine;
}

void GameScene::update(float dt)
{
	stateMachine->update(dt);
}

void GameScene::createQuitButton(string normal, string selected)
{
	auto closeItem = MenuItemImage::create(normal, selected, CC_CALLBACK_1(GameScene::quitGame, this));
	closeItem->setPosition(Point(visibleSize.width / 2, 0));
	closeItem->setAnchorPoint(Point(0.5f, 0));
	SETSIZE(closeItem, 0.08);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}

void GameScene::quitGame(Ref* pSender)
{
	Director::getInstance()->popScene();
}
