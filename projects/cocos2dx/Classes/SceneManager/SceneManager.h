#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__
#include "cocos2d.h"
/************************************************************************/
/*  SceneManager
 *  gwang
 *  提供场景管理
 */                     
/************************************************************************/
class MainMenu;
class Scene1;
class Scene2;
extern const std::string startGameMsg;
extern const std::string continueGameMsg;
extern const std::string quitGameMsg;
extern const std::string backToMenuMsg;
class SceneManager : public cocos2d::Layer 
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(unsigned int);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    SceneManager();
    ~SceneManager();
    // implement the "static create()" method manually
    CREATE_FUNC(SceneManager);
private:
    void __createNewGame(cocos2d::Ref* pSender);
    void __continueGame(cocos2d::Ref* pSender);
    void __backToMenu(cocos2d::Ref* pSender);
    void __addObserver();
    void __cleanObserver();
private:
    unsigned int m_SceneIndex;
    MainMenu* m_pMainMenu;
    Scene1* m_pScene1;
    Scene2* m_pScene2;
    cocos2d::CCNotificationCenter* m_pEventCenter;
};
#endif // !__SCENE_MANAGER__
