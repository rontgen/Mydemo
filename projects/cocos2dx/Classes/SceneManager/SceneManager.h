
/************************************************************************/
/*  SceneManager
*  rontgen
*  提供场景管理
*/
/************************************************************************/

#pragma  once


#include "cocos2d.h"
#include "MyGameDef.h"

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
    static cocos2d::Scene* createScene(uint32 index);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    cocos2d::Scene* getSceneByIndex(uint32 index);

private:
    SceneManager();
    ~SceneManager();
    void __createNewGame(cocos2d::Ref* pSender);
    void __continueGame(cocos2d::Ref* pSender);
    void __backToMenu(cocos2d::Ref* pSender);
    void __addObserver();
    void __cleanObserver();
    void __initSceneMap();
private:
    unsigned int m_SceneIndex;
    MainMenu* m_pMainMenu;
    Scene1* m_pScene1;
    Scene2* m_pScene2;
    cocos2d::__NotificationCenter* m_pEventCenter;
    static cocos2d::Scene* m_pScene;
    std::map<uint32, cocos2d::Scene*>  m_mapScene;
};
