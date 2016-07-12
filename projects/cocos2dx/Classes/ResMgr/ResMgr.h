/**
 *author:rontgen
 *date:2016/01/19-2016/01/20
 *Func Descrip: provider a common interface for res creation
 */
#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "UIScale9Sprite.h"

enum ResType
{
    kSprite = 1 << 1,
    kScale9Sprite = 1 << 2,
    kCsb = 1 << 3,
    kShader = 1 <<4,
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
    cocos2d::Ref* createRes(const std::string& resName, ResType type);
    GLProgramState* createShader(const std::string& vertexStr, const std::string& fragStr);
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
    cocos2d::Ref* __createScale9Sprite(const std::string& pStr);
    cocos2d::Ref* __createCsbLayer(const std::string& pStr);
    cocos2d::GLProgramState* __createShaderProgram(const std::string& pVertexStr, const std::string& pFragStr);

    const std::string& __getPathByKey(const ResType type, const std::string& key);
    void __initResTypeMap();
    void __initMapFromJson(const std::string& mapType, std::map<std::string, std::string>& map, const rapidjson::Document& rjson);
private:
    std::unordered_map<ResType, std::tuple<std::string, std::map<std::string, std::string>>> m_mapResType;
    std::map<std::string, std::string> m_mapImages;
    std::map<std::string, std::string> m_mapLayout;
    std::map<std::string, std::string> m_mapShader;
    std::string m_sImgPathPrefix;
};




