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

///
///	Line positions
///
static const int levelLines[] = 
{
	501,
	386,
	272,
	157,
	43,
	NULL
};

static const int lineThickness = 16;

class MainScene : public cocos2d::CCLayer
{
private:

	void showNoAction(CCPoint pos);

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

	//	Callfunc action
	void removeItemAction(CCNode* node);

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