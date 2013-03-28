#ifndef _BIRD_H_
#define _BIRD_H_

#include "cocos2d.h"
#include <MainScene.h>


enum BirdType 
{
	BirdTypeRegular = 0,
	BirdTypeKing
};


///
///	Bird class 
///
class Bird : public cocos2d::CCLayer
{
protected:
	
	BirdType type;
	cocos2d::CCSprite *m_sprite;

	Bird()
	{
		type = BirdTypeRegular;
		m_sprite = NULL;		
	}

public:

	//	public size getter
	cocos2d::CCSize size;
	cocos2d::CCSprite* sprite;

	virtual bool init();

	CREATE_FUNC(Bird);
};


///
///	Bird King
///
class BirdKing : public Bird
{
public:
	BirdKing() : Bird() 
	{ 
		type = BirdTypeKing;
	}
	CREATE_FUNC(BirdKing);
};


#endif