#include "AppDelegate.h"
#include "MainScene.h"

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

Size visibleSize;
Point origin;

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::createWithRect("StateTest", Rect(0, 0, 960, 640));
		director->setOpenGLView(glview);
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	director->getOpenGLView()->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL); 
	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/item.plist", "sprites/item.png");

	SimpleAudioEngine* audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("musics/bgm.mp3");
	audio->preloadEffect("musics/hurt.wav");
	audio->preloadEffect("musics/extend.wav");
	audio->preloadEffect("musics/bomb.wav");
	audio->preloadEffect("musics/graze.wav");

	// turn on display FPS
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	FileUtils::getInstance()->addSearchPath("res");

	// create a scene. it's an autorelease object
	auto scene = MainScene::create();

	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
