#include "BirdPoo.h"

using namespace cocos2d;

static const float _pooSpeed = 12.0f;

static const bool pooVisible = false;

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

	if (pooVisible)
	{
		sprite = CCSprite::create("poo.png");
		this->addChild(sprite);	
	}

	this->scheduleUpdate();

	return true;
}

void BirdPoo::update(float delta)
{
	float speed = _pooSpeed;
	float posX = this->getPositionX();	
	float posY = this->getPositionY();

	timer += delta;		
	float jumps = 1;
	float freq = 24;	
	float ampl = 42 / (jumpCount + 1);
	float rotation = abs(sin(timer * freq)) * ampl;
	
	float jmpEvent = abs(sin(timer * freq));
	CCLog("rotation: %f", jmpEvent);

	if (direction != PooDirectionCenter && jmpEvent <= 0.1f)
		jumpCount++;

	if (jumpCount == jumps)
	{
		this->removeFromParentAndCleanup(true);
		return;
	}


	//	Check direction
	switch (direction)
	{
		case PooDirectionCenter:
			posY -= speed;
			rotation = 0;
			break;
		case PooDirectionLeft:
			posX -= speed;			
			break;
		case PooDirectionRight:			
			posX += speed;			
			break;
	}
	
	//	Set position
	this->setPosition(posX, posY);

	//	Add some fancy effects (fancy meaning shitty in this case)			
	//this->setRotation(rotation);
	if (rotation)
		this->setPositionY(border + rotation);
	

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
	CCPoint pos = this->getPosition();
	pos.y += 10;

	//	Separate to two new ones
	BirdPoo* left = BirdPoo::create(type, pos.y, PooDirectionLeft);
	BirdPoo* right = BirdPoo::create(type, pos.y, PooDirectionRight);

	left->setPosition(pos);		
	right->setPosition(pos);

	this->getParent()->addChild(left);
	this->getParent()->addChild(right);

	//	Remove myself
	this->removeFromParentAndCleanup(true);
}