
#include "SceneManager.h"
#include "MainMenu.h"
#include "Scene1.h"
#include "Scene2.h"

USING_NS_CC;
const std::string startGameMsg = "start_game";
const std::string continueGameMsg = "continue_game";
const std::string quitGameMsg = "quit_game";
const std::string backToMenuMsg = "back_menu";

Scene* SceneManager::m_pScene = nullptr;

SceneManager::SceneManager() 
               : m_SceneIndex(0)
               , m_pMainMenu(nullptr)
               , m_pScene1(nullptr)
               , m_pScene2(nullptr)
               , m_pEventCenter(nullptr)
{}

SceneManager::~SceneManager()
{}
Scene* SceneManager::createScene(uint32 index)
{
    SceneManager *pRet = new(std::nothrow) SceneManager();
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet->getSceneByIndex(index);
        } 
        else 
        {
            delete pRet; 
            pRet = NULL;
            return NULL;
        }
}
void SceneManager::__addObserver()
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneManager::__createNewGame), startGameMsg, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneManager::__continueGame), continueGameMsg, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneManager::__backToMenu), backToMenuMsg, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneManager::menuCloseCallback), quitGameMsg, NULL);

}

cocos2d::Scene* SceneManager::getSceneByIndex(uint32 index)
{
    auto ite = m_mapScene.find(index);
    if (ite != m_mapScene.end())
    {
        m_pScene = ite->second;
    }
    return m_pScene;
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
    __initSceneMap();
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

void SceneManager::__initSceneMap()
{
    m_mapScene.emplace(gdef::gs::kMainMenu, MainMenu::createScene());
    m_mapScene.emplace(gdef::gs::kScene1, Scene1::createScene());
    m_mapScene.emplace(gdef::gs::kScene1, Scene2::createScene());
}