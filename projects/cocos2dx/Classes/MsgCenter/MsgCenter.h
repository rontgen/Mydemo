/**
  * author: rontgen
  * Func Description: 
  */
#pragma once

#include "cocos2d.h"
#include "CCComponent.h"
#include <functional>
#include <list>
#include <map>
typedef const std::function<void(const cocos2d::Ref*)> callback;
class MsgCenter : public cocos2d::Component
{
public:
    static MsgCenter* instance()
    {
        static MsgCenter ins;
        return &ins;
    }
    void update(float delta) override;
    void addObserver(const std::string msg, callback func);
    void sendMsg(const std::string msg, const cocos2d::Ref* pSender);
private:
    MsgCenter();
    ~MsgCenter();
    MsgCenter(const MsgCenter*);
    MsgCenter& operator = (const MsgCenter*);
private:
    std::map<const std::string, callback> m_mapListener;
    std::list<const std::string> m_list;
    /* todo: remove buffer list and add buffer list */
};

