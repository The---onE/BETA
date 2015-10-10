#pragma once

#include "Global.h"

class EnemyLayer : public Layer
{
public:
	CREATE_FUNC(EnemyLayer);
	Point getEnemyPosition();
	Rect getEnemyRect();
	bool changeHealth(int delta);
	void setHealth(int health);
	void setHealthMax(int healthMax);
	int getHealth();

protected:
	bool init();
	void createEnemy(std::string filename);
	void createHealth(std::string filename);
	void runUpward();
	void runDownward();
	void update(float dt);

	Sprite* Enemy;
	Sprite* Health;
	float healthLength;
	int health;
	int healthMax;
	int enemyFrameNum;
	float enemyAnimateSpeed;
};

