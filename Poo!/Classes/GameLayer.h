#ifndef _GAME_LAYER_H
#define _GAME_LAYER_H

#include "cocos2d.h"

class GameLayer : public cocos2d::CCLayer
{
public:
	cocos2d::CCSprite* sprite;

	GameLayer()
	{
		sprite = NULL;
	}
};

#endif