#include "Animation.h"

using namespace cocos2d;

static const float defaultAnimationSpeed = 1.0f/24;

Animation* Animation::create(const char* map, const char* image,  CCObject* target, SEL_CallFunc sel, int repeat, float animationSpeed)
{
	Animation* m = new Animation(map, image, target, sel, repeat, animationSpeed);
	if (m && m->init())
	{
		m->autorelease();
		return m;
	}

	CC_SAFE_DELETE(m);
	return NULL;
}

Animation* Animation::create(const char* map, const char* image, int repeat, float animationSpeed)
{
	Animation* m = new Animation(map, image, repeat, animationSpeed);
	if (m && m->init())
	{
		m->autorelease();
		return m;
	}

	CC_SAFE_DELETE(m);
	return NULL;
}

bool Animation::init()
{	
	//	Add sprite frames
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(map, image);

	//	Load dict
	CCDictionary* dic = CCDictionary::createWithContentsOfFile(map);
	if (dic)
	{
		//	Load frames		
		dic = (CCDictionary*) dic->objectForKey("frames");

		if (!dic)
			return false;
		
		//	Create spriteframes
		CCArray* names = CCArray::create();
		
		CCDictElement* p = NULL;
		CCDICT_FOREACH(dic, p)
		{
			const char* val = p->getStrKey();
			CCSpriteFrame* fr = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(val);
			names->addObject(fr);
		}
		
		//	Start animation
		if (!animationSpeed)
			animationSpeed = defaultAnimationSpeed;

		animation = CCAnimation::createWithSpriteFrames(names, animationSpeed);		
		animator = CCAnimate::create(animation);

		if (repeatCount == 0)
			repeater = CCRepeatForever::create(animator);
		else 
		{
			CCFiniteTimeAction* a = repeater = CCRepeat::create(animator, repeatCount);

			if (callback && callbackTarget)
			{					
				repeater = CCSequence::createWithTwoActions(a, CCCallFunc::create(callbackTarget, callback));
			}
		}		
		
		return true;
	}

	return false;
}

void Animation::start(CCNode* node)
{
	this->node = node;
	if (node)
		node->runAction(repeater);
}

void Animation::stop()
{
	if (node)
		node->stopAction(repeater);
}