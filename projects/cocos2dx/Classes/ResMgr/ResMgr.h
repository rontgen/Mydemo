#pragma once
#include "cocos2d.h"

enum ResType
{
    kSprite = 1 << 1,
    kCsb
};

class ResMgr : public cocos2d::Ref
{
public:
    static ResMgr* Instance()
    {
        static ResMgr ins;
        return &ins;
    }
    bool initRes();
    cocos2d::Node* createRes(const std::string& resName, ResType type);
    const std::string& getPathFromKey(const std::string& resKey);
private:
    ResMgr();
    ~ResMgr();
    ResMgr(const ResMgr*);
    ResMgr& operator = (const ResMgr*);
private:
    std::map<std::string, std::string> m_mapImages;
};




