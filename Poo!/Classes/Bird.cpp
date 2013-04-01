#include "Bird.h"

using namespace cocos2d;

bool Bird::init()
{
	do
	{
		CC_BREAK_IF(!cocos2d::CCLayer::init());
		
		switch (type)
		{
			case BirdTypeRegular:
				resourceName = "bird.png";
				resourceAnim = "./animations/regular/";
				break;
			case BirdTypeKing:
				resourceName = "king.png";
				resourceAnim = "./animations/king/";
				break;
			case BirdTypeDuke:
				resourceName = "duke.png";
				resourceAnim = "./animations/duke/";
				break;
		};		

		CC_BREAK_IF(!resourceName);

		//	Create sprite
		sprite = CCSprite::create(resourceName);		
		CC_BREAK_IF(!sprite);
		
		size = sprite->getContentSize();

		//	Small position adjustment
		sprite->setAnchorPoint(ccp(0.5, 0));
		sprite->setPosition(ccp(0, -5));		

		this->addChild(sprite);

		this->animateCasual();

		return true;
	} 
	while (false);

	return false;
}

void Bird::animateCasual()
{
	char img[MAX_PATH];
	char map[MAX_PATH];

	sprintf(img, "%s/assetData.png", resourceAnim);
	sprintf(map, "%s/assetData.plist", resourceAnim);

	//	animation
	animation = Animation::create(map, img);
	if (animation)
		animation->start(this->sprite);	
}

void Bird::dropPoo()
{	
	//	Animate crouch
	animateDrop();

	//	Animate poop
	this->runAction(
		CCSequence::createWithTwoActions(
		CCDelayTime::create(0.65f), 
		CCCallFunc::create(this, callfunc_selector(Bird::animatePoop))
	));
}

void Bird::donePoop()
{
	CCLog("DOne poooping!");
	this->sprite->stopAllActions();
	this->animateCasual();
}

void Bird::createPhysics()
{
	int rank = Settings::shared()->memoryRankFromPosition(this->getPosition());	
	int p = Settings::shared()->lineForPosition(rank + 1);

	PooType type = getPooType();
	BirdPoo *poo = BirdPoo::create(type, p);

	CCPoint pos = this->getPosition();
	pos.y -= 20;

	poo->setPosition(pos);
	this->getParent()->addChild(poo);	
}

void Bird::animatePoop()
{
	//
	createPhysics();

	//	Poo animation	
	Animation* a = Animation::create("./Animations/poo/assetData.plist", "./Animations/poo/assetData.png", 1);	
	CCSprite* s = CCSprite::create("poo.png");	
	
	CCPoint pos = this->getPosition();
	pos.y -= 10;
	pos.x -= 0;
	s->setAnchorPoint(ccp(0.5, 1));
	s->setPosition(pos);
	s->setScale(0.7f);
	
	this->getParent()->addChild(s);
	a->start(s);
}

void Bird::animateDrop()
{
	this->sprite->stopAllActions();
	Animation* anim = Animation::create(
		"./animations/regular_crouch/assetData.plist", 
		"./animations/regular_crouch/assetData.png", 
		this,
		callfunc_selector(Bird::donePoop),
		1);
	
	anim->start(this->sprite);
}

PooType Bird::getPooType()
{
	return PooTypeRegular;
}

void Bird::hit()
{
	m_isHit = true;

	//	highlight
	sprite->setColor(ccc3(255, 0, 0));
}