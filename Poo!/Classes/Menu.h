#ifndef _GAME_MENU_H_
#define _GAME_MENU_H_

#include "cocos2d.h"
#include "MainScene.h"
#include "RepeatableSprite.h"

class GameMenu : public cocos2d::CCScene
{
private:

	CCSprite* logo;
	cocos2d::CCMenu* mainMenu;

	void doPlay(CCObject* button);
	void doCredits(CCObject* button);
	void doExit(CCObject* button);

	GameMenu()
	{
		logo = NULL;
		mainMenu = NULL;
	}

	


public:

	virtual bool init();
	CREATE_FUNC(GameMenu);

};

#endif