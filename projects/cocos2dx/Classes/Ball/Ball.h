/**
  * author : gwang
  * Date: 2016-01-25
  * Function Desciption: basic class for ball 
  *                      1. with box2d properties physic properties
  *                      2. rendered with sprite by cocos2dx
  */

#pragma  once

#include "cocos2d.h"
#include "Box2D.h"


enum BallType
{
    kBallInit = 0,
    kBallWhite = 1 << 5,
    kBallCommon,
    kHoleMiddle,
    kHoleCommon,
    kHoleSpecial,
};

class b2dSprite : public cocos2d::Ref
{
public:
    b2dSprite()
        : m_bIsInit(false)
        , m_pSprite(nullptr)
        , m_pB2dBdy(nullptr)
    {}
    ~b2dSprite();
    bool getInitFlag(){ return m_bIsInit; }
    void ChangeInitFlag(bool hasInit){ m_bIsInit = hasInit; }
    void setSprite(cocos2d::Sprite* pSprite){ m_pSprite = pSprite; }
    cocos2d::Sprite* getSprite(){ return m_pSprite; }
    void setB2dBdy(b2Body* pB2dBdy){ m_pB2dBdy = pB2dBdy; }
    b2Body* getB2dBdy() { return m_pB2dBdy; }
private:
    bool m_bIsInit;
    cocos2d::Sprite* m_pSprite;
    b2Body* m_pB2dBdy;
};

class Ball
    : public cocos2d::Ref
{
public:
    Ball();
    virtual ~Ball();
    Ball(const b2World * pB2World
                       , cocos2d::Sprite* pSprite
                       , const b2BodyDef* b2dbdyDef
                       , const b2FixtureDef* b2dFixDef);
    CC_SYNTHESIZE(BallType, m_type, TypeDef);
    bool checkInit(){ return m_pB2dSprite->getInitFlag(); }
    b2dSprite* getB2dSprite() { return m_pB2dSprite; }
 private:
     b2dSprite* m_pB2dSprite;
};

