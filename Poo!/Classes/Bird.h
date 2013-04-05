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

static const std::string animationDir = "./animations/";
static const std::string assetMapFile = "assetData.plist";
static const std::string assetImgFile = "assetData.png";

static const std::string shapeDataFile = ".data";
static const std::string assetDataFile = ".png";

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
		
	std::string resourceDir;
	std::string resourceName;
	
	std::string resourcePNG;

	Bird()
	{
		type = BirdTypeRegular;
		dying = false;
		m_isHit = false;
		
		body = NULL;
		animation = NULL;

	}

	~Bird()
	{
		if (body)
		{
			b2World* w = body->GetWorld();
			if (w) w->DestroyBody(body);
		}
	}

	virtual void animateCasual();
	virtual void animatePoop();

	virtual void updatePositionForBody();

public:

	bool dying;

	virtual void update(float delta);

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