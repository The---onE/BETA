#pragma once
#include "Global.h"
#include "State.h"

//DEFINE_STATE(XXState)��END_DEFINE_STATE����XXState��֮�䶨����Ի�����

DEFINE_STATE(StartState)
END_DEFINE_STATE

DEFINE_STATE(DialogState)
END_DEFINE_STATE

DEFINE_STATE(TrashState)
	float attackInterval;
	float attackTime;
	float trashInterval;
	float trashTime;
END_DEFINE_STATE

DEFINE_STATE(BossState)
	float attackInterval;
	float attackTime;
	float trashInterval;
	float trashTime;
	float danmakuInterval;
	float danmakuTime;
END_DEFINE_STATE

DEFINE_STATE(WinState)
END_DEFINE_STATE

DEFINE_STATE(LoseState)
END_DEFINE_STATE
