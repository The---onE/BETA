#pragma once
#include "Global.h"

class State;
class GameScene;

class StateMachine : public Node
{
protected:
	GameScene* scene;
	State* state;
public:
	bool initWithGameScene(GameScene* scene);
	static StateMachine* createWithGameScene(GameScene* scene);
	State* getState();
	void changeState(State* state);
	void update(float delta);
};