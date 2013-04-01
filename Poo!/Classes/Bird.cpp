#include "Bird.h"

using namespace cocos2d;

bool Bird::init()
{
	do
	{
		CC_BREAK_IF(!cocos2d::CCLayer::init());

		//	Get name
		char *resourceName = NULL;
		char *resourceAnim = NULL;

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

		if (resourceAnim)
		{
			char img[MAX_PATH];
			char map[MAX_PATH];

			sprintf(img, "%s/assetData.png", resourceAnim);
			sprintf(map, "%s/assetData.plist", resourceAnim);

			//	Add sprite frames
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(map, img);

			//	Load dict
			CCDictionary* dic = CCDictionary::createWithContentsOfFile(map);						
			if (dic)
			{
				//	Load frames
				CCArray* names = CCArray::create();
				dic = (CCDictionary*) dic->objectForKey("frames");

				CCDictElement* p = NULL;
				CCDICT_FOREACH(dic, p)
				{
					const char* val = p->getStrKey();
					CCSpriteFrame* fr = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(val);
					names->addObject(fr);
				}
				
				//	Start animation
				CCAnimation* an = CCAnimation::createWithSpriteFrames(names, 1.0/30);
				sprite->runAction(CCRepeatForever::create(CCAnimate::create(an)));

				//	Adjust scale (for now - resources should be correct size)
				sprite->setScale(0.6f);
				
			}
		}

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