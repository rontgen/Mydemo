#pragma once
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"

enum ResType
{
    kSprite = 1 << 1,
    kScale9Sprite = 1 << 2,
    kCsb = 1 << 3,
};
using namespace rapidjson;
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
    const std::string& getPathFromKey(const ResType type, const std::string& resKey);
private:
    ResMgr();
    ~ResMgr();
    ResMgr(const ResMgr*);
    ResMgr& operator = (const ResMgr*);
    bool __checkPathStr(const ResType type, const std::string& pStr);
    void __initResMap(const ResType type, const rapidjson::Document& rjson);
private:
    std::map<std::string, std::string> m_mapImages;
    std::map<std::string, std::string> m_mapLayout;
};




