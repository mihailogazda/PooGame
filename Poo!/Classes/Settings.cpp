#include "Settings.h"

using namespace cocos2d;

Settings *_globalSettings = NULL;
static const int _levelSize = 6;
static const int _lineThickness = 16;

///
///	Line positions
///
static const int levelLines[_levelSize] = 
{
	501,
	386,
	272,
	157,
	43,
	NULL
};

static const int levelLimits[_levelSize] = 
{
	0,
	3,
	5,
	7,
	10,	
	0
};

#pragma region ClassMethods

Settings* Settings::shared()
{
	if (!_globalSettings)
	{
		_globalSettings = new Settings();
	}

	return _globalSettings;
}

CCSize Settings::screenSize()
{
	return CCDirector::sharedDirector()->getWinSizeInPixels();
}

int Settings::levelSize()
{
	return _levelSize;
}

int Settings::lineThickness()
{
	return _lineThickness;
}

int Settings::lineForPosition(int item)
{	
	if (item >= levelSize())
		return 0;
	return levelLines[item];
}

int Settings::limitForLine(int item)
{	
	if (item >= levelSize())
		return 0;
	return levelLimits[item];
}

void Settings::level(void* level, unsigned int* size)
{
	if (level == NULL && size)
	{
		*size = sizeof(levelLines);
		return;
	}
	memcpy(level, levelLines, *size);
}

void Settings::limits(void* level, unsigned int* size)
{
	if (level == NULL && size)
	{
		*size = sizeof(levelLimits);
		return;
	}
	memcpy(level, levelLimits, *size);
}

int Settings::rankFromPosition(CCPoint pos)
{
	int total = Settings::shared()->levelSize();
	int ret = total;
	for (int i = total - 1; i >= 0; i--)
	{
		if (pos.y <= lineForPosition(i))
		{
			ret = (total - 1) - i;
			break;
		}
	}
	return ret;
}

int Settings::memoryRankFromPosition(CCPoint pos)
{
	int re = rankFromPosition(pos);
	if (re == 0)
		return 0;

	return min(_levelSize - re - 1, 0);
}

bool Settings::itemOutOfSight(CCNode* item)
{	
	CCNode* WorldLayer = CCDirector::sharedDirector()->getRunningScene();
	if (WorldLayer)
	{
		CCSize screen = this->screenSize();
		CCPoint pos = WorldLayer->convertToWorldSpace(item->getPosition());
		
		if (pos.x >= screen.width || pos.x <= 0 || pos.y >= screen.height || pos.y <= 0)
			return true;
	}

	return false;
}

#pragma endregion