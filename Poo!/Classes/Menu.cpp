#include "Menu.h"

using namespace cocos2d;

bool GameMenu::init()
{
	//	Super init first
	if (!CCScene::init())
		return false;
	
	CCSize size = CCDirector::sharedDirector()->getWinSizeInPixels();
	char* texture = "crate_steel.png";
	
	RepeatableSprite* r = RepeatableSprite::create(texture, size);
	this->addChild(r);

	/*MorphSprite* morphSprite = MorphSprite::create(texture, "./Shaders/water.fsh", size);
	morphSprite->setPosition(ccp(100, 100));
	morphSprite->setScale(5);
	this->addChild(morphSprite);*/

	logo = CCSprite::create("logo.png");
	logo->setPosition(ccp(size.width / 2 + 110, size.height / 2 + 100));
	this->addChild(logo);

	//	Create menu items
	CCMenuItemFont *play = CCMenuItemFont::create("Play", this, menu_selector(GameMenu::doPlay));	
	play->setAnchorPoint(ccp(0, 0));
	CCMenuItemFont *credits = CCMenuItemFont::create("Credits", this, menu_selector(GameMenu::doCredits));
	credits->setAnchorPoint(ccp(0, 0));
	CCMenuItemFont *exit = CCMenuItemFont::create("Exit", this, menu_selector(GameMenu::doExit));
	exit->setAnchorPoint(ccp(0, 0));
	
	//	Create main menu
	mainMenu = CCMenu::create(play, credits, exit, NULL);
	mainMenu->alignItemsVertically();	
	mainMenu->setPosition(ccp(10, 50));		

	this->addChild(mainMenu);

	return true;
}

void GameMenu::doPlay(CCObject* button)
{
	//	Play MainScene
	CCScene* scene = MainScene::scene();
	CCDirector::sharedDirector()->replaceScene(
		CCTransitionJumpZoom::create(1, scene));
}

void GameMenu::doCredits(CCObject* button)
{
	char* message = ""\
		"\tDevelopment Team:\t\r\n"\
		"\r\n"\
		"\tArt and animation:\t\r\n"\
		"\tIbrahim Abdo"\
		"\r\n\r\n"\
		"\tProgramming:\t\r\n"\
		"\tBojan Cup\t\r\n"
		"\r\n"\
		"\tThank you for playing! :)\t\r\n";

	char* title = "Poo! is Work in Progress";

	MessageBox(CCEGLView::sharedOpenGLView()->getHWnd(), message, title, MB_OK | MB_ICONINFORMATION);
}

void GameMenu::doExit(CCObject* button)
{
	//	Exit
	CCDirector::sharedDirector()->end();
}


