//
//  MorphSprite.h
//  morph
//
//  Created by Radif Sharafullin on 2/21/13.
//
//

#ifndef __morph__MorphSprite__
#define __morph__MorphSprite__

#include "cocos2d.h"

class MorphSprite : public cocos2d::CCSprite, public cocos2d::CCTouchDelegate {
    typedef cocos2d::CCSprite super;
    
    int _timeUniformLocation;
    float _totalTime;
    
    int _touch1PositionXUniformLocation; 
	int _touch1PositionYUniformLocation;
    cocos2d::CCPoint _touch1Position;
    
    int _touch2PositionXUniformLocation; 
	int _touch2PositionYUniformLocation;
    cocos2d::CCPoint _touch2Position;
    
    void initShader(const char *fshFileName);
    void update(float dt);
    
    virtual void onEnter();
    virtual void onExit();
    
    //touches
    cocos2d::CCPoint convertToShaderSpace(const cocos2d::CCPoint & loc, bool & onSpriteArea);
    void convertTouchesIntoShaderPoints(cocos2d::CCSet *pTouches, bool ended=false);

    // optional
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
	const cocos2d::CCTexture2D* texture;

public:
    
	static MorphSprite* create(const char *pszFileName, const char *fshFileName);
	static MorphSprite* create(const char *pszFileName, const char *fshFileName, cocos2d::CCSize size);
	
protected:
    MorphSprite();
    virtual ~MorphSprite();
};

#endif /* defined(__morph__MorphSprite__) */
