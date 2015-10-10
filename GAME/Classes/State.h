#pragma once
#include "Global.h"

#include "GameScene.h"

#define CREATE_STATE(__TYPE__) \
static __TYPE__* create(GameScene* scene) \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet && (pRet->scene=scene) && pRet->entryState()) \
	{ \
        pRet->autorelease(); \
        CC_SAFE_RETAIN(pRet); \
		pRet->time = 0; \
        return pRet; \
	} \
	else \
	{ \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
	} \
}

#define DEFINE_STATE(STATE) class STATE : public State \
{ \
public: \
	CREATE_STATE(STATE); \
	bool checkStateChange(); \
	bool entryState(); \
	void onUpdate(float dt); \
	bool exitState(); \

#define END_DEFINE_STATE };

#define CHANGE_TO_STATE(STATE) {exitState(); scene->getStateMachine()->changeState(STATE::create(scene)); return true;}

class GameScene;

class State : public Node
{
public: 
	GameScene* scene;
	float time;

	virtual bool checkStateChange() = 0; //状态改变返回true，状态未改变返回false，
	virtual bool entryState() = 0;
	virtual void onUpdate(float dt) = 0;
	virtual bool exitState() = 0;
};

