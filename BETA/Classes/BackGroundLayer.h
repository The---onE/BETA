#pragma once

#include "Global.h"

class BackGroundLayer : public Layer
{
public:
	CREATE_FUNC(BackGroundLayer);
	void setSpeed(float speed);

protected:
    bool init();
	void createBackGround(std::string filename);
	void update(float dt);

	Sprite* Bg;
	Sprite* tempBg;
	float speed;
	float BgWidth;
};

