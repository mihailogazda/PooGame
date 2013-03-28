#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#ifdef ENABLE_BOX2D

	#include "Box2D/Box2D.h"
	#pragma comment (lib, "libBox2d.lib")

#endif

#include "SimpleAudioEngine.h"

#include "Bird.h"

using namespace cocos2d;

static const int levelSize = 6;

class Bird;

///
///	Line positions
///
static const int levelLines[levelSize] = 
{
	501,
	386,
	272,
	157,
	43,
	NULL
};

static const int levelLimits[levelSize] = 
{
	0,
	3,
	5,
	7,
	10,	
	0
};

static const int lineThickness = 16;

class MainScene : public cocos2d::CCLayer
{
private:

	//	Gets rank from 0 to levelSize (1 - lowest)
	int getRank(CCPoint pos);

	//	Bird at position
	Bird* getBirdAtPosition(CCPoint pos);

	//	Shows error currsor (animated)
	void showNoAction(CCPoint pos);


	//	Callfunc actions
	void removeItemAction(CCNode* node, void* ptr = NULL);
	void fadeToDeath(Bird* node);
	
	//	Private storage for level limits
	int birds[levelSize];

	MainScene()
	{
		//	Copy settings
		memcpy(birds, levelLimits, sizeof(birds));
	}

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();



	static cocos2d::CCScene* shared();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

	//	movement controls
	virtual void ccTouchesBegan(CCSet* touches, CCEvent* pEvent);
	virtual void ccTouchesMoved(CCSet* touches, CCEvent* pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

    // implement the "static node()" method manually
    CREATE_FUNC(MainScene);
};

#endif  // __HELLOWORLD_SCENE_H__