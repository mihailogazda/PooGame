#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "cocos2d.h"

static const int MAX_LEVEL_SIZE = 10;

class Settings
{
public:
	
	//	Singleton
	static Settings* shared();

	//	Settings
	cocos2d::CCSize screenSize();

	int levelSize();
	int lineThickness();
	
	int lineForPosition(int item);
	int limitForLine(int item);	
	
	//	memory copy
	void level(void* memory, unsigned int *size);
	void limits(void* memory, unsigned int *size);

	int rankFromPosition(cocos2d::CCPoint pos);
	int memoryRankFromPosition(cocos2d::CCPoint pos);

	bool itemOutOfSight(cocos2d::CCNode* item);

};


#endif