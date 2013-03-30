#include "BirdPoo.h"

using namespace cocos2d;

float _pooSpeed = 1.5f;

BirdPoo* BirdPoo::create(PooType t, int border, PooDirection dir)
{
	BirdPoo *p = new BirdPoo(t, border, dir);
	if (p && p->init())
	{				
		p->autorelease();
		return p;		
	}

	CC_SAFE_DELETE(p);
	return NULL;
}

bool BirdPoo::init()
{
	//	Super init
	if (!CCLayer::init())
		return false;

	sprite = CCSprite::create("poo.png");
	this->addChild(sprite);	

	this->scheduleUpdate();

	return true;
}

void BirdPoo::update(float delta)
{
	float speed = _pooSpeed;
	float posX = this->getPositionX();	
	float posY = this->getPositionY();

	timer += 6 * delta;
	float rotation = sin(timer);
	float rotation1 = abs(sin(timer));

	//	Check direction
	switch (direction)
	{
		case PooDirectionCenter:
			posY -= speed;
			break;
		case PooDirectionLeft:
			posX -= speed;
			rotation = rotation1;
			break;
		case PooDirectionRight:			
			posX += speed;
			rotation = rotation1;
			break;
	}

	//	Set position
	this->setPosition(posX, posY);


	//	Add some fancy effects (fancy meaning shitty in this case)
	
	

	

	this->setRotation(rotation);

	//	If border is hit then split
	if (isOutOfBorder())
		split();

	//	If out of sight then remove from map
	if (Settings::shared()->itemOutOfSight(this))
	{
		CCLog("BirdPoo out of sight and killed");
		this->removeFromParentAndCleanup(true);
	}

}

bool BirdPoo::isOutOfBorder()
{
	if (border == 0)
		return false;

	float posY = this->getPositionY();
	if (posY <= border)
		return true;

	return false;
}

void BirdPoo::split()
{
	//	Separate to two new ones
	BirdPoo* left = BirdPoo::create(type, 0, PooDirectionLeft);
	BirdPoo* right = BirdPoo::create(type, 0, PooDirectionRight);

	CCPoint pos = this->getPosition();
	pos.y += 10;

	left->setPosition(pos);		
	right->setPosition(pos);

	this->getParent()->addChild(left);
	this->getParent()->addChild(right);

	//	Remove myself
	this->removeFromParentAndCleanup(true);
}