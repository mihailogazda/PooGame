#ifndef _BIRD_POO_H_
#define _BIRD_POO_H_

#include "cocos2d.h"
#include "Settings.h"

enum PooType
{
	PooTypeRegular,
	PooTypeKing
};

enum PooDirection
{
	PooDirectionCenter,
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

	BirdPoo(PooType t, int b, PooDirection dir) 
	{
		border = b;
		sprite = NULL;
		type = t;
		direction = dir;
	}

	//	separates poo to two
	void split();

public:

	int border;
	PooDirection direction;
	PooType type;
	
	//	init here
	virtual bool init();	
	virtual void update(float delta);

	virtual bool isOutOfBorder();

	//CREATE_FUNC(BirdPoo);
	static BirdPoo* create(PooType t, int border = 0, PooDirection = PooDirectionCenter);

};


#endif