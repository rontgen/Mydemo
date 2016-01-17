#pragma once
#include "cocos2d.h"

class ResMgr : public cocos2d::Ref
{
public:
    ResMgr();
    ~ResMgr();
    static ResMgr* Instance();
    bool initRes();
private:
    static ResMgr* m_sResMgr;
    std::map<std::string, std::string> m_mapImages;
};




