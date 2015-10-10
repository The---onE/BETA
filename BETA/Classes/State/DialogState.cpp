#include "StateList.h"

bool DialogState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��ʹ��CHANGE_TO_STATE(STATE)����״̬
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