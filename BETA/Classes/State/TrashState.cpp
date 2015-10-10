#include "StateList.h"

bool TrashState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��ʹ��CHANGE_TO_STATE(STATE)����״̬
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