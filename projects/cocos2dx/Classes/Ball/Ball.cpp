#include "Ball.h"

Ball::Ball()
    : m_pSprite(nullptr)
    , m_pB2dBdy(nullptr)
    , m_type(kBallInit)
{
}

Ball::~Ball()
{
}