
#include "MainMenu.h"
#include "MyResource.h"
#include "SceneManager.h"
#include "ShaderNode.h"
#include "SpriteBlur.h"
#include "ResMgr.h"

USING_NS_CC;
Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
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
    
    //add start btn
    auto startBtn = MenuItemImage::create(kimgMainMenuBtnStartNormal, kimgMainMenuBtnStartPressed, CC_CALLBACK_1(MainMenu::__menuStartCallback, this));
    //startBtn->setPosition(Vec2(origin.x + visibleSize.width / 2 - startBtn->getContentSize().width / 2,
    //    origin.y + visibleSize.height / 2 + startBtn->getContentSize().height / 2));
    startBtn->setPosition(Vec2((origin.x + visibleSize.width)/2, (origin.y + visibleSize.height)*0.55f));
    startBtn->setTag(MainMenuTag::startBtn);
    //add continue btn
    auto continueBtn = MenuItemImage::create(kimgMainMenuBtnContinueNormal, kimgMainMenuBtnContinuePressed, CC_CALLBACK_1(MainMenu::__menuContinueCallback, this));
    //startBtn->setPosition(Vec2(origin.x + visibleSize.width / 2 - startBtn->getContentSize().width / 2,
    //    origin.y + visibleSize.height / 2 + startBtn->getContentSize().height / 2));
    continueBtn->setPosition(Vec2((origin.x + visibleSize.width) / 2, (origin.y + visibleSize.height)* 0.35f /*+ startBtn->getContentSize().height / 2*/));
    continueBtn->setTag(MainMenuTag::continueBtn);
    //add quit btn
    auto quitBtn = MenuItemImage::create(kimgMainMenuBtnQuitNormal, kimgMainMenuBtnQuitPressed, CC_CALLBACK_1(MainMenu::__menuQuitCallback, this));
    //startBtn->setPosition(Vec2(origin.x + visibleSize.width / 2 - startBtn->getContentSize().width / 2,
    //    origin.y + visibleSize.height / 2 + startBtn->getContentSize().height / 2));
    quitBtn->setPosition(Vec2((origin.x + visibleSize.width) / 2, (origin.y + visibleSize.height)*0.15f /*+ startBtn->getContentSize().height / 2*/));
    quitBtn->setTag(MainMenuTag::quitBtn);

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
        origin.y + closeItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(startBtn, continueBtn, quitBtn, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);

    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Fuck World", "fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    //this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto csb = static_cast<Layer*>(ResMgr::Instance()->createRes("test", ResType::kCsb));
    auto sprite = csb->getChildByName<Sprite*>("img_bg");

    //shader test start
//     auto glProgram = GLProgram::createWithFilenames(kShaderVertexAttributePassShader, kLenseFlareShader);
//     auto glProgramState = GLProgramState::getOrCreateWithGLProgram(glProgram);
//     auto spriteContentSize = sprite->getTexture()->getContentSizeInPixels();
//     glProgramState->setUniformVec2("textureResolution", Vec2(spriteContentSize.width, spriteContentSize.height));
//     glProgramState->setUniformVec2("resolution", Vec2(spriteContentSize.width, spriteContentSize.height));
//     sprite->setGLProgramState(glProgramState);
    //end
    //auto glShaderState = ResMgr::Instance()->createShader("attribute_pass_vertex", "grey_scale");
    //sprite->setGLProgramState(glShaderState);

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    // add the sprite as a child to this layer
    this->addChild(csb, 0);

    auto logo = Sprite::create(kimgMainMenuLogo);
    logo->setPosition(Vec2((origin.x + visibleSize.width) / 2, (origin.y + visibleSize.height)*0.8f));
    this->addChild(logo, 1);
    {
        auto test = SpriteBlur::create(kimgMainMenu.c_str());
        test->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(test, 3);
    }

    auto sn = ShaderNode::shaderNodeWithVertex("", "Shaders/example_Twist.fsh");
    auto s = Director::getInstance()->getWinSize();
    sn->setPosition(Vec2((origin.x + visibleSize.width) / 2, (origin.y + visibleSize.height) / 2));

    sprite->addChild(sn, 2);
    return true;
}


void MainMenu::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainMenu::__menuStartCallback(cocos2d::Ref* pSender)
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(startGameMsg, NULL);
}

void MainMenu::__menuContinueCallback(cocos2d::Ref* pSender)
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(continueGameMsg, NULL);
}       

void MainMenu::__menuQuitCallback(cocos2d::Ref* pSender)
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(quitGameMsg, NULL);
}

void MainMenu::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = CC_CALLBACK_0(MainMenu::__onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
    Node::draw(renderer, transform, flags);
}


void MainMenu::__onDraw(const Mat4 &transform, uint32_t flags)
{
    auto glProgramState = getGLProgramState();
}