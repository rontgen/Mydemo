#pragma once
#include "cocos2d.h"
#include "json/document.h"
#include "UIScale9Sprite.h"

enum ResType
{
    kSprite = 1 << 1,
    kScale9Sprite = 1 << 2,
    kCsb = 1 << 3,
};
USING_NS_CC;
using namespace rapidjson;
namespace cocos2d{
    namespace ui{
        Scale9Sprite;
    }
}

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
    void __getImgPath(const rapidjson::Document& rjson);
    cocos2d::Ref* __createSprite(const std::string& pStr);
    const std::string& getPathByKey(const ResType type, const std::string& key);
private:
    std::map<std::string, std::string> m_mapImages;
    std::map<std::string, std::string> m_mapLayout;
    std::string m_sImgPathPrefix;
};




