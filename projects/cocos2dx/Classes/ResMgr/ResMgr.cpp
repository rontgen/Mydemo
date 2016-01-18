#include "ResMgr.h"

//#include "cocos-ext.h"

USING_NS_CC;

//ResMgr* ResMgr::m_sResMgr = nullptr;

ResMgr::ResMgr()
    :m_mapImages()
{
}

ResMgr::~ResMgr()
{
}

bool ResMgr::initRes()
{
    //load json from file and save
    auto filePath = FileUtils::getInstance()->fullPathForFilename("res_mgr.json");
    auto contentStr = FileUtils::getInstance()->getStringFromFile(filePath);
    rapidjson::Document rapidJson;
    rapidJson.Parse<0>(contentStr.c_str());
    if (rapidJson.HasParseError())  //½âÎö´íÎó  
    {
        log("GetParseError %s\n", rapidJson.GetParseError());
    }
    __initResMap(kSprite, rapidJson);
    __initResMap(kCsb, rapidJson);
    return true;
}

cocos2d::Node* ResMgr::createRes(const std::string& resName, ResType type)
{
    return nullptr;
}

const std::string& ResMgr::getPathFromKey(const ResType type, const std::string& resKey)
{
    switch (type)
    {
    case kScale9Sprite:
    case kSprite:
        {
            CCASSERT(m_mapImages.find(resKey) != m_mapImages.end(), "");
            return m_mapImages.at(resKey);
        }
        break;
    case kCsb:
        {
            CCASSERT(m_mapLayout.find(resKey) != m_mapLayout.end(), "");
            return m_mapLayout.at(resKey);
        }
        break;
    default:
        break;
    }

}

bool ResMgr::__checkPathStr(const ResType type, const std::string& pStr)
{
    //for each str, check if its plist and pack png exist
    //if exist addSprite Frame
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile()
    //else add Texture
    //TextureCache::getInstance()::addImage()
    return true;
}

void ResMgr::__initResMap(const ResType type, const rapidjson::Document& rjson)
{
    switch (type)
    {
    case kSprite:
        {
            if (rjson.IsObject() && rjson.HasMember("images"))
            {
                const rapidjson::Value& membersObject = rjson["images"];
                for (rapidjson::Value::ConstMemberIterator it = membersObject.MemberonBegin(); it != membersObject.MemberonEnd(); it++)
                {
                    m_mapImages.insert(std::make_pair(std::string(it->name.GetString()), std::string(it->value.GetString())));
                }
            }
        }
        break;
    case kCsb:
        {
            if (rjson.IsObject() && rjson.HasMember("csb"))
            {
                const rapidjson::Value& membersObject = rjson["csb"];
                for (rapidjson::Value::ConstMemberIterator it = membersObject.MemberonBegin(); it != membersObject.MemberonEnd(); it++)
                {
                    m_mapLayout.insert(std::make_pair(std::string(it->name.GetString()), std::string(it->value.GetString())));
                }
            }
        }
        break;
    default:
        break;
    }
}