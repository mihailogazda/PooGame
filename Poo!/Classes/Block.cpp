#include "Block.h"

using namespace cocos2d;
bool seedWasAssigned = false;

static int randomInInterval(int min, int max)
{
	if (!seedWasAssigned)
	{
		srand(time(0));
		seedWasAssigned = true;
	}
    return min + (rand() % (int)(max - min + 1));
}

bool Block::init()
{
	if (!CCLayer::init())
		return false;

	int ran = randomInInterval(1, 2);
	char* name = ran == 1 ? "crate_wood.png" : "crate_steel.png";
		
	sprite = CCSprite::create(name);
	if (!sprite)
		return false;

	sprite->setAnchorPoint(ccp(0.5, 0));
	this->addChild(sprite);

	return true;
}