#include "StateList.h"

bool LoseState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��ʹ��CHANGE_TO_STATE(STATE)����״̬
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