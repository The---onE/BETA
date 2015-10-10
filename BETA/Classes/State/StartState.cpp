#include "StateList.h"

bool StartState::checkStateChange() //状态改变返回true，状态未改变返回false，使用CHANGE_TO_STATE(STATE)更改状态
{
	if (time > 0)
		CHANGE_TO_STATE(DialogState);
	return false;
}

bool StartState::entryState()
{
	return true;
}

void StartState::onUpdate(float dt)
{
	time += dt;
}

bool StartState::exitState()
{
	return true;
}