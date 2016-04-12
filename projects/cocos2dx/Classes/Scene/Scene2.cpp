#include "Scene2.h"
#include "SceneManager.h"
#include "ResMgr.h"

USING_NS_CC;

Scene* Scene2::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = Scene2::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Scene2::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(Scene2::menuCloseCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
        origin.y + closeItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Scene2", "fonts/Marker Felt.ttf", 24);
    label->setColor(Color3B(0,255.f,255.f));

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto pBg = static_cast<Sprite*>(ResMgr::Instance()->createRes("bg_test", ResType::kSprite));

    // position the sprite on the center of the screen
    pBg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    auto pWaveTest = static_cast<Sprite*>(ResMgr::Instance()->createRes("wave_test", ResType::kSprite));
    auto glState = ResMgr::Instance()->createShader("wave_shader_vertex", "wave_shader_frag");
    auto spriteContentSize = pWaveTest->getTexture()->getContentSizeInPixels();
    glState->setUniformVec2("resolution", Vec2(spriteContentSize.width, spriteContentSize.height));
    glState->setUniformTexture("tex0", pWaveTest->getTexture());
    pWaveTest->setGLProgramState(glState);
    auto winSize = Director::getInstance()->getWinSize();
    pWaveTest->setPosition(Vec2(/*visibleSize.width / 2 + origin.x*/winSize.width / 2.f, /*visibleSize.height / 2 + origin.y*/winSize.height/2.f));
    // add the sprite as a child to this layer
    this->addChild(pBg, 0);
    this->addChild(pWaveTest, 1);
    //auto csbLayer = static_cast<cocos2d::Layer*>(ResMgr::Instance()->createRes("test", ResType::kCsb));
    //this->addChild(csbLayer);
    return true;
}


void Scene2::menuCloseCallback(Ref* pSender)
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(backToMenuMsg);
}
