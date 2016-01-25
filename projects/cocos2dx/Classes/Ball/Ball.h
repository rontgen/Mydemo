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

class Ball
{
public:
    Ball();
    virtual ~Ball();

    enum BallType
    {
        kBallInit = 0,
        kBallWhite = 1 << 5,
        kBallCommon,
        kHoleMiddle,
        kHoleCommon,
        kHoleSpecial,
    };
protected:
    cocos2d::Sprite* m_pSprite;
    b2Body* m_pB2dBdy;
    BallType m_type;
};

