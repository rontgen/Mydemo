#ifndef __SCENE__
#define __SCENE__
#include "cocos2d.h"
//�̳�coco2dxScene�Ļ��࣬ÿ����������̳������
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
    //��������
    int32 index;
    //�������泡����Ϣ
    SceneInfo* m_pSceneInfo;
};
#endif // !__SCENE__
