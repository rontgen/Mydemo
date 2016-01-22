#include "MsgCenter.h"


USING_NS_CC;

MsgCenter::MsgCenter()
    : m_mapListener()
    , m_list()
{

}

MsgCenter::~MsgCenter()
{
    m_mapListener.clear();
    m_list.clear();
}

void MsgCenter::addObserver(const std::string msg, callback func)
{
    if (m_mapListener.find(msg)!= m_mapListener.end())
    {
        return;
    }
    m_mapListener.insert(std::make_pair(msg, func));
}

void MsgCenter::sendMsg(const std::string msg, const cocos2d::Ref* pSender)
{
    if (m_mapListener.find(msg) != m_mapListener.end())
    {
        auto func = m_mapListener[msg];
        func(pSender);
    }
}

void MsgCenter::update(float delta)
{
    //1.mutex thread
    //2. check if m_queue is empty
    //3. if not empty, pop msg and sendMsg
}

