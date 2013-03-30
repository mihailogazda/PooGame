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

#pragma endregion