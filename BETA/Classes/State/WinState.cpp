#include "StateList.h"

bool WinState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��ʹ��CHANGE_TO_STATE(STATE)����״̬
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