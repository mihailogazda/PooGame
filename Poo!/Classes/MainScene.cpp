#include "MainScene.h"

using namespace cocos2d;

CCScene* _globalMainScene = NULL;

CCScene* MainScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MainScene *layer = MainScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);

		//	save for shared
		_globalMainScene = scene;

    } while (0);

    // return the scene
    return scene;
}

CCScene* MainScene::shared()
{
	return _globalMainScene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

              
        // Get window size 
        CCSize size = CCDirector::sharedDirector()->getWinSize();


        // 3. Add add a splash screen, show the cocos2d splash image.
		CCSprite* pSprite = NULL;
		pSprite = CCSprite::create("background.png");//MorphSprite::create("background.png", "./Shaders/static_tv_outline.fsh");
		if (!pSprite)
			pSprite = CCSprite::create("background.png");
        CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to MainScene layer as a child layer.
        this->addChild(pSprite, 0);
		

		//	Add king
		createKing();
		
		//	Add menu
		createMenu();

		//	Enable touch controls
		this->setTouchEnabled(true);

        bRet = true;
    } while (0);

    return bRet;
}

void MainScene::createKing()
{
	CCSize size = CCDirector::sharedDirector()->getWinSizeInPixels();
	theKing = BirdKing::create();				

	float toX = size.width / 2;
	float toY = Settings::shared()->lineForPosition(0);

	theKing->setPosition(ccp(toX, toY));		
	this->addChild(theKing);				
}

void MainScene::doSplat(CCObject* button)
{
	theKing->dropPoo();
}

void MainScene::createMenu()
{
	CCMenuItemFont *f = CCMenuItemFont::create("Splat!", this, menu_selector(MainScene::doSplat));

	CCMenu *m = CCMenu::create(f, NULL);

	CCSize size = CCDirector::sharedDirector()->getWinSizeInPixels();	
	CCPoint pos = ccp(size.width - 60, size.height - 30);
	m->setPosition(pos);

	this->addChild(m);
}

void MainScene::ccTouchesBegan(CCSet* pTouches, CCEvent* pEvent)
{
	CCPoint touchPos = getTouchPos(pTouches);
	selected = getBirdAtPosition(touchPos);

	if (selected && selected->dying)
		selected = NULL;

	if (selected)
		originalPos = selected->getPosition();
}

CCPoint MainScene::getTouchPos(CCSet* pTouches)
{
	CCTouch* touch = (CCTouch*) pTouches->anyObject();
	CCPoint touchPos = touch->getLocationInView();
	//	Invert Y
	touchPos.y = CCDirector::sharedDirector()->getWinSizeInPixels().height - touchPos.y;
	return touchPos;
}

void MainScene::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
	if (!selected)
		return;

	CCTouch* touch = (CCTouch*) touches->anyObject();

	CCPoint prevLoc = touch->getPreviousLocationInView();
	CCPoint newLoc = touch->getLocationInView();

	CCPoint diff = ccpSub(newLoc, prevLoc);
	diff.y = 0;	//	no movement on Y axis	

	CCPoint loc = ccpAdd(selected->getPosition(), diff);
	loc.x = clampX(loc.x);
	selected->setPosition(loc);
	
}

void MainScene::ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent)
{	
	if (selected)
	{
		CCPoint diff = ccpSub(selected->getPosition(), originalPos);
		selected = NULL;

		//	do nothing if moved
		if (abs(diff.x) >= 2)
			return;
	}
	
	CCPoint touchPos = getTouchPos(pTouches);
	Settings *settings = Settings::shared();

	//	get rank in visual and memory
	int total = settings->levelSize();
	int rank = settings->rankFromPosition(touchPos);
	int memoryRank = total/* + 1*/ - rank;	
	
	//	Check if its in the King area or in empty - block it
	if ( rank <= 1 || rank == total)
	{
		showNoAction(touchPos);
		return;
	}	
	//	check for lines - block it
	else
	{
		for (int i = 0; i < total; i++)
		{
			int pos = settings->lineForPosition(i);
			if (touchPos.y <= pos && touchPos.y >= pos - settings->lineThickness())
			{
				showNoAction(touchPos);
				return;
			}			
		}
	}

	//	Check if bird exists if it does delete it
	Bird *b = NULL;	
	b = getBirdAtPosition(touchPos);
	if (b && !b->dying)
	{
		fadeToDeath(b);
		birds[memoryRank]++;
		return;
	}
	else if (birds[memoryRank] <= 0)
	{
		showNoAction(touchPos);
		return;
	}

	
	//	If not then add the birds
	switch (rank)
	{
		case 5:
			b = BirdDuke::create();
			break;
		default:
			b = Bird::create();			
	}

	b->setPosition(touchPos);
	this->addChild(b);

	//	Add birds to limiter
	birds[memoryRank]--;
	
	//	Set to correct position
	touchPos.x = clampX(touchPos.x);
	touchPos.y = Settings::shared()->lineForPosition(total - rank);

	//	Move
	b->runAction(CCEaseIn::create(CCMoveTo::create(0.5, touchPos), 1));	
}

int MainScene::clampX(int x)
{
	float r = 0;
	CCSize size = CCDirector::sharedDirector()->getWinSizeInPixels();
	r = max(sceneMargin, x);
	r = min(size.width - sceneMargin, r);
	return r;
}



Bird* MainScene::getBirdAtPosition(CCPoint pos)
{
	CCArray* children = this->getChildren();
	for (unsigned int i = 0; i < children->count(); i++)
	{
		CCObject* child = children->objectAtIndex(i);
		Bird* ret = dynamic_cast<Bird*>(child);
		if (!ret)
			continue;
		
		//	Check if in position
		CCSize size = ret->sprite->getContentSize();
		CCPoint ps = ret->getPosition();

		CCRect rect = CCRectMake(ps.x, ps.y, size.width, size.height);		
		rect.origin.x -= size.width / 2;

		/*
		`*****
		******
		
		******
		**`***
		*/


		if (rect.containsPoint(pos))
			return ret;
	}


	return NULL;
}

void MainScene::removeItemAction(CCNode* node, void* ptr)
{
	CCNode* ob = ptr != NULL ? (CCNode*) ptr : node;
	
	if (ob)
		ob->removeFromParentAndCleanup(true);			
}

void MainScene::fadeToDeath(Bird* node)
{
	CCCallFuncN *callfuncn = CCCallFuncND::create(this, callfuncND_selector(MainScene::removeItemAction), node);	
	CCFadeOut* f = CCFadeOut::create(0.5f);
	CCSequence* s = CCSequence::createWithTwoActions(f, callfuncn);
	node->dying = true;

	node->sprite->runAction(s);
}


void MainScene::showNoAction(CCPoint pos)
{
	CCSprite *no = CCSprite::create("no.png");
	no->setPosition(pos);		
	this->addChild(no);		

	CCFadeTo* hide = CCFadeTo::create(0.5f, 0);
	CCCallFuncN * remove = CCCallFuncND::create(this, callfuncND_selector(MainScene::removeItemAction), NULL);

	no->runAction(CCSequence::createWithTwoActions(hide, remove));
}