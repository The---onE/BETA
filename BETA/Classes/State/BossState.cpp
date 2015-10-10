#include "StateList.h"

bool BossState::checkStateChange() //状态改变返回true，状态未改变返回false，使用CHANGE_TO_STATE(STATE)更改状态
{
	if (scene->checkLose())
		CHANGE_TO_STATE(LoseState);
	if (scene->checkWin())
		CHANGE_TO_STATE(WinState)
	return false;
}

bool BossState::entryState()
{
	scene->initBoss(); 
	
	attackTime = 0;
	attackInterval = 0.5f;
	scene->setBulletSpeed(15.0f);

	trashTime = 0;
	trashInterval = 1.8f;
	scene->setTrashSpeed(5.4f);

	danmakuTime = 0;
	danmakuInterval = 2.8f;

	return true;
}

void BossState::onUpdate(float dt)
{
	time += dt;
	time += dt;
	attackTime += dt;
	if (attackTime > attackInterval)
	{
		attackTime = 0;
		scene->attack();
	}
	trashTime += dt;
	if (trashTime > trashInterval)
	{
		trashTime = 0;
		scene->trashAttack();
	}
	danmakuTime += dt;
	if (danmakuTime > danmakuInterval)
	{
		danmakuTime = 0;
		scene->danmakuAttack(5, 75, 24.0f);
	}
	scene->checkBullet();
	scene->checkTrash();
	scene->checkDanmaku();
}

bool BossState::exitState()
{
	return true;
}