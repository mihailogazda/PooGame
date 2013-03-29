#ifndef _BIRD_POO_H_
#define _BIRD_POO_H_

#include "cocos2d.h"

enum PooType
{
	PooTypeRegular,
	PooTypeKing
};

enum PooDirection
{
	PooDirectionLeft,
	PooDirectionRight
};


///
///	Represents drop from a birds ass.
///	Also known as Poo or Crap.
///
class BirdPoo : public cocos2d::CCLayer
{
private:

	//	Holds image data
	cocos2d::CCSprite* sprite;

	BirdPoo()
	{
	}

public:

	PooDirection direction;
	PooType type;
	
	//	init here
	virtual bool init();	

	CREATE_FUNC(BirdPoo);
};


#endif