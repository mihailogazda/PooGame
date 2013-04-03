#ifndef _REPEATABLE_SPRITE_H_
#define _REPEATABLE_SPRITE_H_

#include "cocos2d.h"

///
///	RepeatableSprite class
///	Fills rectangle with repeatable texture. It should be pow2 textures.
///
class RepeatableSprite : public cocos2d::CCLayer
{
private:

	const char* textureName;
	cocos2d::CCSize size;
	cocos2d::CCTexture2D *texture;
	
	RepeatableSprite(const char* filename, cocos2d::CCSize size)
	{
		textureName = filename;
		this->size = size;
		texture = NULL;
	}

public:

	//	Getters
	cocos2d::CCTexture2D* getTexture() { return texture; }
	cocos2d::CCSize getSize() { return size; }

	//	Init
	virtual bool init()
	{
		bool ret = false;
		do
		{
			CC_BREAK_IF(!cocos2d::CCLayer::init());

			texture = cocos2d::CCTextureCache::sharedTextureCache()->addImage(textureName);
			CC_BREAK_IF(!texture);
		
			ccTexParams params = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
			texture->setTexParameters(&params);	
		
			CCSprite* back = CCSprite::createWithTexture(texture, CCRectMake(0, 0, size.width, size.height));
			CC_BREAK_IF(!back);

			back->setAnchorPoint(ccp(0, 0));
			this->addChild(back);

			ret = true;
		}
		while (false);

		return ret;
	}

	static RepeatableSprite* create(const char* filename, const cocos2d::CCSize size)
	{
		RepeatableSprite* ret = new RepeatableSprite(filename, size);
		if (ret && ret->init())
		{
			ret->autorelease();
		}
		else
			CC_SAFE_DELETE(ret);

		return ret;
	}

};

#endif