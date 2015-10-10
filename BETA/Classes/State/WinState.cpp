#include "StateList.h"

bool WinState::checkStateChange() //状态改变返回true，状态未改变返回false，使用CHANGE_TO_STATE(STATE)更改状态
{
	return false;
}

bool WinState::entryState()
{
	scene->win();

	return true;
}

void WinState::onUpdate(float dt)
{
}

bool WinState::exitState()
{
	return true;
}