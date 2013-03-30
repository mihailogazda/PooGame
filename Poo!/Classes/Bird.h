#ifndef _BIRD_H_
#define _BIRD_H_

#include "cocos2d.h"
#include "BirdPoo.h"

enum BirdType 
{
	BirdTypeRegular = 0,
	BirdTypeKing,
	BirdTypeDuke
};


///
///	Bird class 
///
class Bird : public cocos2d::CCLayer
{
protected:
	
	BirdType type;
	cocos2d::CCSprite *m_sprite;

	virtual PooType getPooType();

	Bird()
	{
		type = BirdTypeRegular;
		m_sprite = NULL;		
		dying = false;
	}

public:

	bool dying;

	//	public size getter
	cocos2d::CCSize size;
	cocos2d::CCSprite* sprite;

	virtual bool init();

	virtual void dropPoo();

	CREATE_FUNC(Bird);
};


///
///	Bird King
///
class BirdKing : public Bird
{
protected:
	virtual PooType getPooType() { return PooTypeKing; }
public:
	BirdKing() : Bird()
	{
		type = BirdTypeKing;
	}
	CREATE_FUNC(BirdKing);
};

class BirdDuke : public Bird
{
public:
	BirdDuke() :  Bird()
	{
		type = BirdTypeDuke;
	}
	CREATE_FUNC(BirdDuke);
};


#endif