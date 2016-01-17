#ifndef __SPRTIE_BLUR__
#define __SPRTIE_BLUR__
#include "cocos2d.h"
USING_NS_CC;
class SpriteBlur : public Sprite
{
public:
    ~SpriteBlur();
    bool initWithTexture(Texture2D* texture, const Rect&  rect);
    void initGLProgram();

    static SpriteBlur* create(const char *pszFileName);
    void setBlurRadius(float radius);
    void setBlurSampleNum(float num);

protected:
    float _blurRadius;
    float _blurSampleNum;
};
#endif