#ifndef __SHAPE_HELPER_H__
#define __SHAPE_HELPER_H__

#include <cocos2d.h>
#include <fstream>
#include <Box2D\Box2D.h>
#include "json.h"
#include "Physics.h"
//#include "Settings.h"

//	JSON LIB HELP HERE
//	http://jsoncpp.sourceforge.net/




class Shape 
{
public:
	std::string name;
	std::string imagePath;
	std::list<b2PolygonShape> polygons;

	Shape(std::string key, string path, std::list<b2PolygonShape> pol) : name(key), imagePath(path), polygons(pol)
	{
	}
};

class ShapeHelper : public cocos2d::CCObject
{
private:

	std::list<Shape*> shapes;

	const char* resourcePath;
	bool init();

	Json::Value rigidBodies;
	Json::Value itemWithName(char* name);

	bool defineShapeFromData(Json::Value data, __out std::list<b2PolygonShape> *shapes);

	ShapeHelper(const char* resourcePath)
	{
		this->resourcePath = resourcePath;		
	}

	~ShapeHelper()
	{
		std::list<Shape*>::iterator ptr;
		for (ptr = shapes.begin(); ptr != shapes.end(); ptr++)
		{
			CC_SAFE_DELETE(*ptr);
		}
	}

public:
	
	
	//	CreateFunc
	static ShapeHelper* create(const char* filename);

	///	Gets b2PolygonShape for asset name
	bool shapeForKey(char* name, cocos2d::CCSize size, __out std::list<b2PolygonShape> *out);
};


#endif