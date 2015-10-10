#include "StateList.h"

bool LoseState::checkStateChange() //状态改变返回true，状态未改变返回false，使用CHANGE_TO_STATE(STATE)更改状态
{
	
	return false;
}

bool LoseState::entryState()
{
	scene->lose();

	return true;
}

void LoseState::onUpdate(float dt)
{

}

bool LoseState::exitState()
{
	return true;
}