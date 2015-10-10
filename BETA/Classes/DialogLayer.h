#pragma once

#include "Global.h"
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;

class DialogLayer : public Layer
{
public:
	CREATE_FUNC(DialogLayer);
	bool isFinish();

protected:
	bool init();
	void onEnter();
	void createBox(string filename);
	void deleteBox();
	void createSkip(string filenameN, string filenameS);
	void Skip();
	void loadText(string filename);
	void loadStage(int stageIndex);
	const char* loadDialog(int dialogIndex);
	void createDialogSprite();
	void createCharacter();
	void showDialog();
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	/*//////////////////////////////////////////////////*/
	KEYBOARD_FUNCTION;
	/*//////////////////////////////////////////////////*/

	tinyxml2::XMLDocument* doc;
	tinyxml2::XMLElement* text;
	tinyxml2::XMLElement* stage;
	tinyxml2::XMLElement* dialog;
	string character;
	string playerFolder;
	string enemyFolder;
	int stageProcess;
	int dialogProcess;
	int dialogCount;
	Sprite* box;
	Label* dialogSprite;
	std::string dialogText;
	Sprite* playerPicture;
	Sprite* enemyPicture;
	bool FinishFlag;
};

