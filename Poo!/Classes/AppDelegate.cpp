#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "Resource.h"
#include "Menu.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
	
	CCEGLView::sharedOpenGLView()->setFrameSize(800, 600);
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	//	Little hack
#ifdef CC_PLATFORM_WIN32
	SetCurrentDirectory("..\\Resources\\");

	//	Set window size
	extern HINSTANCE hGlobalInstance;

	HWND window = CCEGLView::sharedOpenGLView()->getHWnd();
	SetWindowText(window, "Poo!");

	HICON icon = LoadIcon(hGlobalInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
	SendMessage(window, WM_SETICON, (WPARAM) ICON_SMALL, (LPARAM) icon);
#endif

    // create a scene. it's an autorelease object
	CCScene *pScene = GameMenu::create();//MainScene::scene();

    // run
    pDirector->runWithScene(pScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
