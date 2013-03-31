#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "cocos2d.h"
#include "GameLayer.h"

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


///
///	My pretty litle template class for finding objects in level
///
template <class FinderType>
class Finder
{

public:

	static FinderType* findAtPosition(cocos2d::CCPoint pos, cocos2d::CCNode* parent)
	{
		if (!parent)
			return NULL;

		CCArray* children = parent->getChildren();
		for (unsigned int i = 0; i < children->count(); i++)
		{
			CCObject* child = children->objectAtIndex(i);
			FinderType* ret = dynamic_cast<FinderType*>(child);
			if (!ret)
				continue;
		
			//	Check if in position
			CCSize size = CCSizeZero;
			if (dynamic_cast<GameLayer*>(ret) != NULL)
				size = ((GameLayer*)ret)->sprite->getContentSize();
			else
				size = ret->getContentSize();

			CCPoint ps = ret->getPosition();

			CCRect rect = CCRectMake(ps.x, ps.y, size.width, size.height);
			
			rect.origin.x -= size.width / 2;//anchor point - i should check for it (TODO)

			if (rect.containsPoint(pos))
				return ret;
		}

		return NULL;
	}
};


#endif