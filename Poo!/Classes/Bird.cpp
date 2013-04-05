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
				resourceName = "regular";
				resourceDir = animationDir + resourceName + "/";
				break;
			case BirdTypeKing:
				resourceName = "king";
				resourceDir = animationDir + resourceName + "/";
				break;
			case BirdTypeDuke:
				resourceName = "duke";
				resourceDir = animationDir + resourceName + "/";
				break;
		};		

		CC_BREAK_IF(resourceName.empty());

		//	Save full PNG path
		resourcePNG = resourceDir + resourceName + assetDataFile;		

		//	Create sprite
		sprite = CCSprite::create( resourcePNG.c_str() );
		CC_BREAK_IF(!sprite);

		//	Small position adjustment
		sprite->setAnchorPoint(ccp(0.5f, 0));
		//sprite->setPosition(ccp(0, -5));				
		this->addChild(sprite);

		//	Animate casual
		this->animateCasual();

		//	Schedule update
		this->scheduleUpdate();

		return true;
	} 
	while (false);

	return false;
}

void Bird::animateCasual()
{
	std::string map = resourceDir + assetMapFile;
	std::string img = resourceDir + assetImgFile;

	//	animation
	animation = Animation::create(map.c_str(), img.c_str());
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
	//sprite->setColor(ccc3(255, 0, 0));
	CCSprite* splash = CCSprite::create("poo_splash.png");

	splash->setPositionY(10);
	splash->setScale(0.5f);

	this->addChild(splash);
}

bool Bird::initBody(b2World* world)
{
	do
	{
		//	Add bird body
		CC_BREAK_IF(!world);

		CCSize size = sprite->getContentSize();
		CCPoint pos = this->getPosition();

		size.width *= sprite->getScale();
		size.height *= sprite->getScale();

		//	Body def
		b2BodyDef d;
		d.position.Set(SCREEN_TO_WORLD(pos.x), SCREEN_TO_WORLD(pos.y));
		d.type = b2_staticBody;
		d.userData = this;

		body = world->CreateBody(&d);
		CC_BREAK_IF(!body);

		//	Get custom shape
		string path = resourceDir + resourceName + shapeDataFile;
		ShapeHelper* s = ShapeHelper::create(path.c_str());
		CC_BREAK_IF(!s);

		//	Get shapes
		list<b2PolygonShape> shapes;		
		
		string res = resourceName + assetDataFile;
		bool sh = s->shapeForKey(res.c_str(), size, &shapes);
		CC_BREAK_IF(!sh);

		b2FixtureDef fixtureDef;
		
		fixtureDef.isSensor = true;
		fixtureDef.userData = this;		

		/*
		-- BOX SHAPE WORKS
		b2PolygonShape ps;
		ps.SetAsBox(SCREEN_TO_WORLD(size.width / 2), SCREEN_TO_WORLD(size.height / 2));
		fixtureDef.shape = &ps;

		body->CreateFixture(&fixtureDef);
		*/

		//	have to recalculate total weight?
		std::list<b2PolygonShape>::iterator it;
		for (it = shapes.begin(); it != shapes.end(); it++)
		{
			b2PolygonShape p = *(it);			
			fixtureDef.shape = &p;
			body->CreateFixture(&fixtureDef);
		}
		
		return true;

	} while (false);
	
	if (body)
	{
		body->GetWorld()->DestroyBody(body);
		body = NULL;
	}

	return false;
}

void Bird::update(float delta)
{
	updatePositionForBody();
}

void Bird::updatePositionForBody()
{
	if (body)
	{
		float x = this->getPositionX();
		float y = this->getPositionY();
		float a = 0;

		y += sprite->getContentSize().height / 2;

		x = SCREEN_TO_WORLD(x);
		y = SCREEN_TO_WORLD(y);

		body->SetTransform(b2Vec2(x, y), a);
	}
}
