#include "StateList.h"

bool DialogState::checkStateChange() //状态改变返回true，状态未改变返回false，使用CHANGE_TO_STATE(STATE)更改状态
{
	if (scene->isDialogFinish())
		CHANGE_TO_STATE(TrashState);
	return false;
}

bool DialogState::entryState()
{
	scene->initDialog();
	return true;
}

void DialogState::onUpdate(float dt)
{
	time += dt;
}

bool DialogState::exitState()
{
	scene->removeDialog();
	return true;
}