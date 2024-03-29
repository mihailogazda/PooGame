#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Bird.h"
#include "Block.h"
#include "MorphSprite.h"
#include "Settings.h"
#include "Physics.h"

using namespace cocos2d;

class Bird;
class BirdKing;

class MainScene : public cocos2d::CCLayer
{
private:			

	//	Box2D settings
	b2World* world;
	B2DebugDrawLayer* worldDebug;	
	bool initBox2D();

	GameLayer* selected;
	
	//	Layer that holds birds and poo's
	CCLayer* gameContent;

	//	Points and score
	bool wasInitiated;
	int points;
	float timeInitiated;

	CCPoint originalPos;

	//	Shows error currsor (animated)
	void showNoAction(CCPoint pos);

	int clampX(int pos);

	static const int sceneMargin = 30;

	//	Callfunc actions
	void removeItemAction(CCNode* node, void* ptr = NULL);
	void fadeToDeath(Bird* node);

	CCPoint getTouchPos(CCSet* touches);
	
	//	Private storage for level limits
	int birds[MAX_LEVEL_SIZE];

	void doSplat(CCObject* button);
	void doRestart(CCObject*  button);

	CCMenuItemToggle *crateToggler;
	void doToggleBlock(CCObject* button);


	void createBackground();
	void createMenu();

	BirdKing* theKing;
	void createKing();

	void gameOver();

	MainScene()
	{
		//	Copy settings
		unsigned int size = sizeof(birds);
		Settings::shared()->limits(birds, &size);

		selected = NULL;
		originalPos = CCPointZero;
		gameContent = NULL;

		points = 0;
		wasInitiated = false;

		crateToggler = NULL;
		timeInitiated = 0;

		world = NULL;
		worldDebug = NULL;
	}

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
	static cocos2d::CCScene* shared();

	virtual void update(float delta);
    
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