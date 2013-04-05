#ifndef _PHYSICS_H_
#define _PHYSICS_H_

//	Enable box2
#define ENABLE_BOX2D TRUE

#ifdef ENABLE_BOX2D

	#include "Box2D/Box2D.h"
	#include "B2DebugDrawLayer.h"
	#include "ShapeHelper.h"

#endif


#define BOX_WORLD_GRAVITY			-15.0f
#define BOX_WOLRD_STEP				1.0f / 60.0f
#define BOX_WORLD_VELOCITY_PASSES	8.0f
#define BOX_WORLD_POSITION_PASSES	2.0f

#define PTM_RATIO 40.0f
#define SCREEN_TO_WORLD(n) ((n) / PTM_RATIO)
#define WORLD_TO_SCREEN(n) ((n) * PTM_RATIO)
#define B2_ANGLE_TO_COCOS_ROTATION(n) (-1 * CC_RADIANS_TO_DEGREES(n))
#define COCOS_ROTATION_TO_B2_ANGLE(n) (CC_DEGREES_TO_RADIANS(-1 * n))


#endif