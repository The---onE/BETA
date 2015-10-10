#pragma once

#include "Global.h"
#include "Controller.h"

class PlayerLayer : public CR::Controller
{
public:
	CREATE_FUNC(PlayerLayer);
	bool changeHealth(int delta);
	void setHealth(int health);
	void setHealthMax(int healthMax);
	int getHealth();
	Point getPlayerPosition();
	Rect getPlayerRect();

protected:
	bool init();
	void createPlayer(string filename);
	void createHealth(string filename);
	void onEnter();
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	void update(float dt);

	Sprite* Player;
	Sprite* Health;
	float healthLength;
	int health;
	int healthMax;
};