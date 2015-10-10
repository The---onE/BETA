#include "DialogLayer.h"

bool DialogLayer::init()
{
#define boxSizeX 1
#define boxSizeY 0.4
#define skipItemSize 0.16
#define skipItemPositionX visibleSize.width*0.5
#define dialogFontSize 50
#define dialogSizeX 0.8
#define dialogSizeY 0.24
#define dialogPositionX visibleSize.width*0.1
#define dialogPositionY visibleSize.height*0.32
#define playerPictureSize 0.5
#define playerPicturePositionX visibleSize.width*0.1
#define playerPicturePositionY visibleSize.height*0.4
#define enemyPictureSize 0.5
#define enemyPicturePositionX visibleSize.width*0.9
#define enemyPicturePositionY visibleSize.height*0.4

	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("dialogs/box.plist", "dialogs/box.png");

		FinishFlag = false;

		stageProcess = 0;
		dialogProcess = 0;

		createBox("b_0.png");
		createSkip("skip_n.png", "skip_s.png");

		playerFolder = "dialogs/";
		enemyFolder = "dialogs/";
		loadText("dialogs/Text.xml");
		loadStage(stageProcess);
		showDialog();
		dialogProcess++;

		bRet = true;
	} while (0);
	return bRet;
}

void DialogLayer::onEnter()
{
 	CCLayer::onEnter();
 
 	auto listener = EventListenerTouchOneByOne::create();
 	listener->setSwallowTouches(true);
 	listener->onTouchBegan = CC_CALLBACK_2(DialogLayer::onTouchBegan, this);
 	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	/*//////////////////////////////////////////////////*/
	KEYBOARD_LISTENER(DialogLayer);
	/*//////////////////////////////////////////////////*/
}

/*//////////////////////////////////////////////////*/
void DialogLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
  	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
	case EventKeyboard::KeyCode::KEY_KP_ENTER:
		if (dialogProcess < dialogCount)
		{
			showDialog();
			dialogProcess++;
		}
		else
		{
			FinishFlag = true;
		}
		break;
	default:
		break;
	}
}

void DialogLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	default:
		break;
	}
}
/*//////////////////////////////////////////////////*/

void DialogLayer::createBox(std::string filename)
{
	this->removeChild(box);
	box = Sprite::createWithSpriteFrameName(filename);
	box->setAnchorPoint(Point(0, 0));
	box->setScaleX(visibleSize.width/box->getContentSize().width*boxSizeX);
	box->setScaleY(visibleSize.height/box->getContentSize().height*boxSizeY);
	this->addChild(box);
}

void DialogLayer::deleteBox()
{
	this->removeChild(box);
}

void DialogLayer::createSkip(std::string filenameN, std::string filenameS)
{
	MenuItemImage* skipItem = MenuItemImage::create();
	skipItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameN));
	skipItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameS));
	skipItem->setCallback(CC_CALLBACK_0(DialogLayer::Skip, this));

	SETSIZE(skipItem, skipItemSize);
	skipItem->setAnchorPoint(Point(0.5, 0));
	skipItem->setPosition(Point(origin.x + skipItemPositionX, origin.y));
	Menu* pMenu = Menu::create(skipItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu);
}

void DialogLayer::Skip()
{
	FinishFlag = true;
}

void DialogLayer::loadText(std::string filename)
{
	doc = new tinyxml2::XMLDocument;
	Data data = CCFileUtils::getInstance()->getDataFromFile(filename);
	doc->Parse((const char*)data.getBytes());
	text = doc->RootElement();
}

void DialogLayer::loadStage(int stageIndex)
{
	char name[32];
	sprintf(name, "s_%d", stageIndex);
	stage = text->FirstChildElement(name);
	dialogCount = stage->IntAttribute("count");
}

const char* DialogLayer::loadDialog(int dialogIndex)
{
	char name[32];
	sprintf(name, "d_%d", dialogIndex);
	dialog = stage->FirstChildElement(name);
	const tinyxml2::XMLAttribute *characterAttribute = dialog->FirstAttribute();
	return characterAttribute->Value();
}

void DialogLayer::createDialogSprite()
{
	this->removeChild(dialogSprite);
	dialogText = dialog->GetText();
	dialogSprite = Label::createWithTTF(dialogText, "fonts/SourceHanSansCN-Normal.otf", dialogFontSize, Size(visibleSize.width*dialogSizeX, visibleSize.height*dialogSizeY),TextHAlignment::LEFT,TextVAlignment::TOP);
	dialogSprite->setAnchorPoint(Point(0, 1));
	dialogSprite->setPosition(Point(origin.x + dialogPositionX, origin.y + dialogPositionY));
	this->addChild(dialogSprite);
}

void DialogLayer::createCharacter()
{
	this->removeChild(playerPicture);
	this->removeChild(enemyPicture);
	switch ((character.c_str())[0])
	{
	case 'p':
		character = playerFolder + character;
		playerPicture = Sprite::create(character);
		SETSIZE(playerPicture, playerPictureSize);
		playerPicture->setAnchorPoint(Point(0, 0));
		playerPicture->setPosition(Point(origin.x + playerPicturePositionX, origin.y + playerPicturePositionY));
		this->addChild(playerPicture);
		break;

	case 'e':
		character = enemyFolder + character;
		enemyPicture = Sprite::create(character);
		SETSIZE(enemyPicture, enemyPictureSize);
		enemyPicture->setAnchorPoint(Point(1, 0));
		enemyPicture->setPosition(Point(origin.x + enemyPicturePositionX, origin.y + enemyPicturePositionY));
		this->addChild(enemyPicture);
		break;

	default:
		break;
	}
}

void DialogLayer::showDialog()
{
	character = loadDialog(dialogProcess);
	character = character + ".png";
	createDialogSprite();
	createCharacter();
}

bool DialogLayer::isFinish()
{
	return FinishFlag;
}

bool DialogLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
 	if (dialogProcess < dialogCount)
 	{
 		showDialog();
 		dialogProcess++;
 	}
 	else
 	{
 		FinishFlag = true;
 	}

	return false;
}