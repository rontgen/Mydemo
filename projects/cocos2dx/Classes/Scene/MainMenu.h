#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "cocos2d.h"
class MainMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
private:
    void __onDraw(const cocos2d::Mat4& transform, uint32_t flags);
    void __menuStartCallback(cocos2d::Ref* pSender);
    void __menuContinueCallback(cocos2d::Ref* pSender);
    void __menuQuitCallback(cocos2d::Ref* pSender);
    cocos2d::CCNotificationCenter* m_pNotification;
    cocos2d::CustomCommand _customCommand;
    enum MainMenuTag
    {
        startBtn = 0<< 1,
        continueBtn = 1 << 1,
        quitBtn = 2 << 1,
    };
};

#endif // __MAINMENU_H__
