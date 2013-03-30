#include "Bird.h"

using namespace cocos2d;

bool Bird::init()
{
	do
	{
		CC_BREAK_IF(!cocos2d::CCLayer::init());

		//	Get name
		char *resourceName = NULL;

		switch (type)
		{
			case BirdTypeRegular:
				resourceName = "bird.png";
				break;
			case BirdTypeKing:
				resourceName = "king.png";
				break;
			case BirdTypeDuke:
				resourceName = "duke.png";
				break;
		};

		CC_BREAK_IF(!resourceName);

		//	Create sprite
		m_sprite = cocos2d::CCSprite::create(resourceName);		
		CC_BREAK_IF(!m_sprite);

		sprite = m_sprite;
		size = m_sprite->getContentSize();

		//	Small position adjustment
		sprite->setAnchorPoint(ccp(0.5, 0));
		sprite->setPosition(ccp(0, -5));


		this->addChild(m_sprite);

		return true;
	} 
	while (false);

	return false;
}

void Bird::dropPoo()
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