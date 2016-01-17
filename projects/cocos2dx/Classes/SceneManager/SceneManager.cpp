
#include "SceneManager.h"
#include "../Scene/MainMenu.h"
#include "../Scene/Scene1.h"
#include "../Scene/Scene2.h"

USING_NS_CC;
const std::string startGameMsg = "start_game";
const std::string continueGameMsg = "continue_game";
const std::string quitGameMsg = "quit_game";
const std::string backToMenuMsg = "back_menu";
static Scene* m_pScene = nullptr;
SceneManager::SceneManager() 
               : m_SceneIndex(0)
               , m_pMainMenu(nullptr)
               , m_pScene1(nullptr)
               , m_pScene2(nullptr)
               , m_pEventCenter(nullptr)
{}

SceneManager::~SceneManager()
{}
Scene* SceneManager::createScene(unsigned int index)
{
    auto scene = Scene::create();
    auto nullLayer = SceneManager::create();
    switch (index)
    {
    case 0:
        {
            auto layer = MainMenu::create();
            scene->addChild(layer);
            //__addObserver();
        }
        break;
    case 1:
        {
            auto layer = Scene1::create();
            scene->addChild(layer);
           // __addObserver();
        }
        break;
    case 2:
        {
            auto layer = Scene2::create();
            scene->addChild(layer);
            //__addObserver();
        }
        break;
    default:
        //__addObserver();
        break;
    }
  
    // return the scene
    m_pScene = scene;
    return scene;
}
void SceneManager::__addObserver()
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneManager::__createNewGame), startGameMsg, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneManager::__continueGame), continueGameMsg, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneManager::__backToMenu), backToMenuMsg, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneManager::menuCloseCallback), quitGameMsg, NULL);

}
// on "init" you need to initialize your instance
bool SceneManager::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    __addObserver();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    return true;
}


void SceneManager::menuCloseCallback(Ref* pSender)
{
    __cleanObserver();
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void SceneManager::__createNewGame(cocos2d::Ref* pSender)
{
    auto scene = Scene::create();
    auto layer = Scene1::create();
    scene->addChild(layer);
    auto director = Director::getInstance();
    director->replaceScene(scene);
}

void SceneManager::__continueGame(cocos2d::Ref* pSender)
{
    auto scene = Scene::create();
    auto layer = Scene2::create();
    scene->addChild(layer);
    auto director = Director::getInstance();
    director->replaceScene(scene);
}

void SceneManager::__backToMenu(cocos2d::Ref* pSender)
{
    auto scene = Scene::create();
    auto layer = MainMenu::create();
    scene->addChild(layer);
    auto director = Director::getInstance();
    director->replaceScene(scene);
}

void SceneManager::__cleanObserver()
{
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}