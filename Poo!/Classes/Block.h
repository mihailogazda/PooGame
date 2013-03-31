#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "cocos2d.h"
#include "GameLayer.h"

class Block : public GameLayer
{
public:
	
	virtual bool init();

	CREATE_FUNC(Block);
};


#endif