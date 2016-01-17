#include "ResMgr.h"
#include "json/rapidjson.h"
#include "json/document.h"
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
    else if (rapidJson.IsObject() && rapidJson.HasMember("images"))
    {
        const rapidjson::Value& membersObject = rapidJson["images"];
        for (rapidjson::Value::ConstMemberIterator it = membersObject.MemberonBegin(); it != membersObject.MemberonEnd(); it++)
        {
            m_mapImages.insert(std::make_pair(std::string(it->name.GetString()), std::string(it->value.GetString())));
        }
    }
    return true;
}

cocos2d::Node* ResMgr::createRes(const std::string& resName, ResType type)
{
    return nullptr;
}

const std::string& ResMgr::getPathFromKey(const std::string& resKey)
{
    CCASSERT(m_mapImages.find(resKey) != m_mapImages.end(), "");
    return m_mapImages.at(resKey);
}