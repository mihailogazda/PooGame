#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "cocos2d.h"

///
///	My animation class for automated animations from Cocos2d spritesheets
///
class Animation : public cocos2d::CCObject
{
private:

	cocos2d::CCNode* node;

	const char* map;
	const char* image;

	cocos2d::CCAnimate* animator;
	cocos2d::CCAnimation* animation;	
	cocos2d::CCFiniteTimeAction* repeater;

	int repeatCount;
	float animationSpeed;

	cocos2d::SEL_CallFunc callback;
	cocos2d::CCObject* callbackTarget;

	void _reset()
	{		
		repeater = NULL;
		animator = NULL;
		animation = NULL;
		callback = NULL;
		callbackTarget = NULL;		
	}

public:

	Animation(const char* map, const char* image, int repeat = 0, float animationSpeed = 0)
	{
		_reset();
		this->map = map;
		this->image = image;
		this->repeatCount = repeat;
		this->animationSpeed = animationSpeed;		
	}

	Animation(const char* map, const char* image, cocos2d::CCObject* target, cocos2d::SEL_CallFunc sel,  int repeat = 0, float animationSpeed = 0)
	{	
		_reset();
		this->map = map;
		this->image = image;
		this->repeatCount = repeat;
		this->animationSpeed = animationSpeed;
		callbackTarget = target;
		callback = sel;
	}

	~Animation()
	{
		//stop();
	}

	virtual bool init();

	virtual void start(cocos2d::CCNode* node);
	virtual void stop();

	static Animation* create(const char* map, const char* image, int repeat = 0, float animationSpeed = 0);
	static Animation* create(const char* map, const char* image, cocos2d::CCObject* target, cocos2d::SEL_CallFunc sel, int repeat = 0, float animationSpeed = 0);

};

#endif