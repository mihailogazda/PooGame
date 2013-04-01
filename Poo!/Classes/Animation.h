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
	cocos2d::CCRepeatForever* repeater;

public:

	Animation(const char* map, const char* image)
	{
		this->map = map;
		this->image = image;
		repeater = NULL;
		animator = NULL;
		animation = NULL;
	}

	~Animation()
	{
		//stop();
	}

	virtual bool init();

	virtual void start(cocos2d::CCNode* node);
	virtual void stop();

	static Animation* create(const char* map, const char* image);

};

#endif