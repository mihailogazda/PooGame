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
		// super init first
        CC_BREAK_IF(! CCLayer::init());
              
		//	Create background
		createBackground();


		//	Create world content node
		this->gameContent = CCLayer::create();
		this->addChild(gameContent);

		//	Add king
		createKing();
		
		//	Add menu
		createMenu();

		//	Enable touch controls
		this->setTouchEnabled(true);
		this->scheduleUpdate();

        bRet = true;
    } while (0);

    return bRet;
}

void MainScene::createBackground()
{
	CCSprite* pSprite = NULL;
	CCSize size = Settings::shared()->screenSize();
	
	pSprite = CCSprite::create("background.png");//MorphSprite::create("background.png", "./Shaders/static_tv_outline.fsh");    
    pSprite->setPosition(ccp(size.width/2, size.height/2));    
    this->addChild(pSprite, 0);

	//	Add grass to each line with shader effect
	for (int i = 0; i < Settings::shared()->levelSize(); i++)
	{
		int posY = Settings::shared()->lineForPosition(i);
		MorphSprite *g = MorphSprite::create("grass_down.png", "./Shaders/Bend_down.fsh");
		g->setAnchorPoint(ccp(0, 1));
		g->setPositionY(posY);

		this->addChild(g);
	}
}

void MainScene::createKing()
{
	//	First create the King
	CCSize size = CCDirector::sharedDirector()->getWinSizeInPixels();
	theKing = BirdKing::create();				

	float toX = size.width / 2;
	float toY = Settings::shared()->lineForPosition(0);

	theKing->setPosition(ccp(toX, toY));		
	this->gameContent->addChild(theKing);		


	//	Then create the last row
	int rank = Settings::shared()->levelSize() - 2;
	int total = Settings::shared()->limitForLine(rank);
	int width = theKing->sprite->getContentSize().width;
	int margin = (size.width - (total * (width + 5) ) ) / total;

	toX = width;
	toY = Settings::shared()->lineForPosition(rank);	
	
	
	for (int i = 0; i < total; i++)
	{
		Bird* b = Bird::create();
		b->setPosition(toX, toY);

		toX += margin + width;
		this->birds[rank]--;

		this->gameContent->addChild(b);
	}
	
}

void MainScene::doRestart(CCObject* button)
{
	//	Manual - ask the user
	if (button != NULL)
	{
		if (MessageBox(CCEGLView::sharedOpenGLView()->getHWnd(), "Are you sure?", "Restart level?", MB_ICONQUESTION | MB_YESNO) != IDYES)
			return;
	}

	wasInitiated = false;
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1, MainScene::scene()));
}

void MainScene::doSplat(CCObject* button)
{
	theKing->dropPoo();
	wasInitiated = true;
	
	CCMenuItemFont* f = dynamic_cast<CCMenuItemFont*>(button);
	if (f)
		f->setEnabled(false);

}

void MainScene::doToggleBlock(CCObject* button)
{
	CCMenuItemToggle* t = dynamic_cast<CCMenuItemToggle*>(button);
	if (t)
	{
		CCLog("Toggle: %d", t->getSelectedIndex());
	}
}

void MainScene::createMenu()
{
	CCMenuItemFont *f = CCMenuItemFont::create("Splat!", this, menu_selector(MainScene::doSplat));
	CCMenuItemFont *f2 = CCMenuItemFont::create("Restart", this, menu_selector(MainScene::doRestart));
	
	CCMenuItemFont *fblock1 = CCMenuItemFont::create("Blocks");
	CCMenuItemFont *fblock2 = CCMenuItemFont::create("Birds");

	crateToggler =  CCMenuItemToggle::createWithTarget(this, menu_selector(MainScene::doToggleBlock), fblock1, fblock2, NULL);
	

	f2->setScale(0.5f);
	crateToggler->setScale(0.5f);

	//	Create menu
	CCMenu *m = CCMenu::create(f, f2, crateToggler, NULL);

	CCSize size = CCDirector::sharedDirector()->getWinSizeInPixels();	
	CCPoint pos = ccp(size.width - 120, size.height - 30);
	m->setPosition(pos);

	m->alignItemsHorizontally();
	this->addChild(m);
}

void MainScene::ccTouchesBegan(CCSet* pTouches, CCEvent* pEvent)
{
	CCPoint touchPos = getTouchPos(pTouches);
	Bird* selectedBird = Finder<Bird>::findAtPosition(touchPos, gameContent);
	Block* selectedBlock = Finder<Block>::findAtPosition(touchPos, gameContent);

	if (selectedBird && !selectedBird->dying)
		selected = selectedBird;
	if (selectedBlock)
		selected = selectedBlock;

	if (selected)
	{
		selected->setZOrder(10);
		originalPos = selected->getPosition();
	}
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
	if (!selected || wasInitiated)
		return;

	//	Get Touches and move the sprite
	CCTouch* touch = (CCTouch*) touches->anyObject();

	CCPoint prevLoc = touch->getPreviousLocationInView();
	CCPoint newLoc = touch->getLocationInView();

	CCPoint diff = ccpSub(newLoc, prevLoc);
	diff.y = 0;	//	no movement on Y axis	

	CCPoint loc = ccpAdd(selected->getPosition(), diff);
	loc.x = clampX(loc.x);
	selected->setPosition(loc);

	//	Color if on top
	CCRect selectedR;
	selectedR.size = selected->sprite->getContentSize();
	selectedR.origin = selected->getPosition();

	CCArray* children = gameContent->getChildren();
	for (unsigned int i = 0; i < children->count(); i++)
	{
		GameLayer* layer = dynamic_cast<GameLayer*>(children->objectAtIndex(i));
		if (!layer || layer == selected)
			continue;
		
		CCRect r;
		r.size = layer->sprite->getContentSize();
		r.origin = layer->getPosition();

		if (r.intersectsRect(selectedR))
		{
			selected->sprite->setColor(ccc3(255, 0, 0));
			break;
		}
		else
			selected->sprite->setColor(ccc3(255, 255, 255));	


	}

}

void MainScene::ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent)
{	
	if (wasInitiated)
		return;	

	if (selected)
	{
		if (selected->sprite->getColor().b == 0)
		{
			selected->runAction(CCMoveTo::create(1, originalPos));
			selected->sprite->setColor(ccc3(255, 255, 255));
			return;
		}

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

	
	//	Check if crates or birds
	CCLayer *b = NULL;	
	if (crateToggler->getSelectedIndex() == 0)
	{
		b = Finder<Bird>::findAtPosition(touchPos, gameContent);
		if (b && !((Bird*)b)->dying)
		{
			fadeToDeath((Bird*) b);
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

		//	Add birds to limiter
		birds[memoryRank]--;
	}
	else
	{
		b = Finder<Block>::findAtPosition(touchPos, gameContent);
		if (b)
		{
			b->removeFromParentAndCleanup(true);
			return;
		}

		b = Block::create();
	}

	
	if (!b)
		return;

	//	Set position and add
	b->setPosition(touchPos);
	this->gameContent->addChild(b, 10);

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

void MainScene::update(float delta)
{
	if (wasInitiated)
	{
		CCArray* children = this->gameContent->getChildren();
		int pooCount = 0;

		for (unsigned int i =0; i < children->count(); i++)
		{
			CCLayer *l = dynamic_cast<CCLayer*>(children->objectAtIndex(i));
			BirdPoo *p = dynamic_cast<BirdPoo*>(l);

			if (p)
			{
				pooCount++;

				CCPoint pooPos = p->getPosition();			
				Bird* b = Finder<Bird>::findAtPosition(pooPos, gameContent);
				Block* bl = Finder<Block>::findAtPosition(pooPos, gameContent);

				if (bl)
				{
					p->removeFromParentAndCleanup(true);
					return;
				}

				if (b && !b->isHit())
				{
					//	Counter
					points++;

					//	Found hit item - color it
					b->hit();

					//	Continue cascade
					b->dropPoo();

					//	Remove that poo that hit it
					p->removeFromParentAndCleanup(true);
				}
			}
		}

		//	Check if shiting is over
		if (pooCount == 0)
		{
			//	Its all done
			char text[500] = {0};
			char note[200] = {0};

			sprintf_s(text, "You won %d points!\r\n%s", points, note);

			MessageBox(CCEGLView::sharedOpenGLView()->getHWnd(), text, "Score", MB_OK | MB_ICONINFORMATION);

			doRestart(NULL);
		}
	}

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