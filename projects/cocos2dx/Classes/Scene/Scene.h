#ifndef __SCENE__
#define __SCENE__
#include "cocos2d.h"
//继承coco2dxScene的基类，每个场景都会继承这个类
class SceneInfo;
class GameScene : public cocos2d::Scene
{
public:
    GameScene();
    ~GameScene();
    bool init();
    virtual Scene* loadScene(int32);
    virtual void saveScene(SceneInfo*);

protected:

private:
    //场景索引
    int32 index;
    //用来保存场景信息
    SceneInfo* m_pSceneInfo;
};
#endif // !__SCENE__
