#ifndef _BIRD_H_
#define _BIRD_H_

#include "cocos2d.h"
#include "GameLayer.h"
#include "BirdPoo.h"
#include "Animation.h"
#include "Physics.h"
#include "Settings.h"

enum BirdType 
{
	BirdTypeRegular = 0,
	BirdTypeKing,
	BirdTypeDuke
};


///
///	Bird class 
///
class Bird : public GameLayer
{
protected:

	b2Body* body;	
	
	Animation* animation;
	BirdType type;	

	bool m_isHit;

	virtual PooType getPooType();

	virtual void animateDrop();
	virtual void donePoop();

	virtual void createPhysics();	

	const char* resourceName;
	const char* resourceAnim;

	Bird()
	{
		type = BirdTypeRegular;
		dying = false;
		m_isHit = false;
		resourceName = NULL;
		resourceAnim = NULL;
	}

	virtual void animateCasual();
	virtual void animatePoop();

public:

	bool dying;

	//	public size getter
	cocos2d::CCSize size;	

	virtual bool init();
	virtual bool initBody(b2World* world);
	
	virtual void hit();
	virtual bool isHit() { return m_isHit; }

	
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