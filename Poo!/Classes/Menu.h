#ifndef _GAME_MENU_H_
#define _GAME_MENU_H_

#include "cocos2d.h"


class GameMenu : public cocos2d::CCScene
{
private:

	cocos2d::CCMenu* mainMenu;

	GameMenu()
	{
		mainMenu = NULL;
	}

public:

	virtual bool init();
	CREATE_FUNC(GameMenu);

};

#endif