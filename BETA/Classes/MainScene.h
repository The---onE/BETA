#pragma once

#include "Global.h"

class MainScene : public Scene
{
public:
	CREATE_FUNC(MainScene);
	bool init();

protected:
	void StartGame();
	void PlayStopBGM();
	void OpenCloseEffect();
	void QuitGame();
	void createBackGround(string filename);

	Size visibleSize;
	Point origin;
	bool effectFlag;
};

