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
        CCSprite* pSprite = CCSprite::create("background.png");
        CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to MainScene layer as a child layer.
        this->addChild(pSprite, 0);
		

		//	Add king
		Bird *b = BirdKing::create();				

		float toX = size.width / 2;
		float toY = levelLines[0];

		b->setPosition(ccp(toX, toY));		
		this->addChild(b);				
		

		//	Enable touch controls
		this->setTouchEnabled(true);

        bRet = true;
    } while (0);

    return bRet;
}

void MainScene::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

void MainScene::ccTouchesBegan(CCSet* touches, CCEvent* pEvent)
{
}

void MainScene::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
}

void MainScene::ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent)
{
	int total = sizeof(levelLines) / sizeof(int);

	CCTouch* touch = (CCTouch*) pTouches->anyObject();
	CCPoint touchPos = touch->getLocationInView();

	touchPos.y = CCDirector::sharedDirector()->getWinSizeInPixels().height - touchPos.y;

	int rank = getRank(touchPos);
	
	//	Check if its in the King area or in empty - block it
	if ( rank <= 1 || rank == 6)
	{
		showNoAction(touchPos);
		return;
	}
	//	check for lines - block it
	else
	{
		int i = 0;
		while (levelLines[i] != NULL)
		{
			int pos = levelLines[i];
			if (touchPos.y <= pos && touchPos.y >= pos - lineThickness)
			{			
				showNoAction(touchPos);
				return;
			}
			i++;
		}
	}

	//	Add bird
	Bird *b = NULL;
	
	if (touchPos.y >= levelLines[1])
		b = BirdDuke::create();
	else
		b = Bird::create();


	b->setPosition(touchPos);
	this->addChild(b);
	
	
	//	Set to correct position
	touchPos.y = levelLines[total - rank];
	b->runAction(CCEaseIn::create(CCMoveTo::create(0.5, touchPos), 1));
	

}

int MainScene::getRank(CCPoint pos)
{
	int total = sizeof(levelLines) / sizeof(levelLines[0]);
	int ret = total;
	for (int i = total - 1; i >= 0; i--)
	{
		if (pos.y <= levelLines[i])
		{
			ret = (total - 1) - i;
			break;
		}
	}
	return ret;
}

void MainScene::removeItemAction(CCNode* node)
{
	node->removeFromParentAndCleanup(true);
	//CC_SAFE_DELETE(node);
}

void MainScene::showNoAction(CCPoint pos)
{
	CCSprite *no = CCSprite::create("no.png");
	no->setPosition(pos);		
	this->addChild(no);		

	CCFadeTo* hide = CCFadeTo::create(0.5f, 0);
	CCCallFuncN * remove = CCCallFuncN::create(this, callfuncN_selector(MainScene::removeItemAction));

	no->runAction(CCSequence::createWithTwoActions(hide, remove));
}