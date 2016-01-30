#include "Ball.h"

Ball::Ball()
    : m_type(kBallInit)
    , m_pB2dSprite(nullptr)
{
}

Ball::~Ball()
{
}

Ball::Ball(const b2World * pB2World
    , cocos2d::Sprite* pSprite
    , const b2BodyDef* b2dbdyDef
    , const b2FixtureDef* b2dFixDef)
{
    CC_ASSERT(!pSprite, "[Ball][create]: pSprite is nullptr!");
    m_pB2dSprite->setSprite(pSprite);
    m_pB2dSprite->getB2dBdy()->CreateFixture(b2dFixDef);
}