#include "StateList.h"

bool TrashState::checkStateChange() //状态改变返回true，状态未改变返回false，使用CHANGE_TO_STATE(STATE)更改状态
{
	if (scene->checkLose())
		CHANGE_TO_STATE(LoseState);
	if (scene->getScore() > 16)
		CHANGE_TO_STATE(BossState);
	return false;
}

bool TrashState::entryState()
{
	scene->initTrash();

	attackTime = 0;
	attackInterval = 0.5f;
	scene->setBulletSpeed(15.0f);

	trashTime = 0;
	trashInterval = 0.9f;
	scene->setTrashSpeed(4.8f);

	return true;
}

void TrashState::onUpdate(float dt)
{
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
	scene->checkBullet();
	scene->checkTrash();
}

bool TrashState::exitState()
{
	return true;
}