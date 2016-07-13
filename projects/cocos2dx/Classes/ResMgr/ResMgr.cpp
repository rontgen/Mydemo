#include "ResMgr.h"
#include "CSLoader.h"
#include "rapidjson.h"

USING_NS_CC;
using namespace cocos2d::ui;
//ResMgr* ResMgr::m_sResMgr = nullptr;

ResMgr::ResMgr()
    : m_sImgPathPrefix("")
{
    m_mapResType.clear();
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
    /* 解析错误 */
    if (rapidJson.HasParseError())    
    {
        log("GetParseError %s\n", rapidJson.GetParseError());
    }
    __getImgPath(rapidJson);
    __initResTypeMap();
    __initResMap(kSprite, rapidJson);
    __initResMap(kCsb, rapidJson);
    __initResMap(kShader, rapidJson);
    __initScale9ResTypeMap();
    return true;
}

void ResMgr::__initScale9ResTypeMap()
{
    m_mapResType.emplace(ResType::kScale9Sprite, m_mapResType[ResType::kSprite]);
}

cocos2d::Ref* ResMgr::createRes(const std::string& resName, ResType type)
{
    cocos2d::Ref* pNd = nullptr;
    switch (type)
    {
    case kSprite:
        {
            return __createSprite(resName);
        }
        break;
    case kScale9Sprite:
        {
             return __createScale9Sprite(resName);
        }
        break;
    case kCsb:
        {
            return __createCsbLayer(resName);
        }
        break;
    default:
        break;
    }
    return pNd;
}

GLProgramState* ResMgr::createShader(const std::string& vertexStr, const std::string& fragStr)
{
    return __createShaderProgram(vertexStr, fragStr);
}
const std::string ResMgr::getPathFromKey(const ResType type, const std::string& resKey)
{
    if (m_mapResType.find(type) != m_mapResType.end())
    {
        auto map = std::get<1>(m_mapResType[type]);
        CCASSERT(map.find(resKey) != map.end(), "");
        return map.at(resKey);
    }
}

bool ResMgr::__checkPathStr(const ResType type, const std::string& pStr)
{
    //for each str, check if its plist and pack png exist
    //if exist addSprite Frame
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile()
    //else add Texture
    //TextureCache::getInstance()::addImage()
    auto kLength = std::string("images/").size();
    auto path = __getPathByKey(type, pStr);
    auto subFolderPath = path.substr(kLength);
    auto folderName = subFolderPath.substr(0, subFolderPath.find_first_of("/"));
    auto pListPath = m_sImgPathPrefix + folderName + ".plist";
    auto pngPath = m_sImgPathPrefix + folderName + ".png";
    switch (type)
    {
        case kSprite:
        case kScale9Sprite:
        {
            if (FileUtils::getInstance()->isFileExist(pListPath)
                && FileUtils::getInstance()->isFileExist(pngPath))
            {
                SpriteFrameCache::getInstance()->addSpriteFramesWithFile(pListPath);
                if (SpriteFrameCache::getInstance()->getSpriteFrameByName(path))
                {
                    return true;
                }
                return false;
            } 
            else
            {
                TextureCache::getInstance()->addImage(path);
                return false;
            }
        }
        break;
    default:
        break;
    }
    return true;
}

void ResMgr::__initResTypeMap()
{
    m_mapResType.clear();
    m_mapResType.emplace(ResType::kCsb, std::tie("csb", std::map<std::string, std::string>()));
    m_mapResType.emplace(ResType::kSprite, std::tie("images", std::map<std::string, std::string>()));
    m_mapResType.emplace(ResType::kShader, std::tie("shader", std::map<std::string, std::string>()));
}

void ResMgr::__initMapFromJson(const std::string& mapType, std::map<std::string, std::string>& map, const rapidjson::Document& rjson)
{
    if (rjson.IsObject() && rjson.HasMember(mapType.c_str()))
    {
        map.clear();
        const rapidjson::Value& membersObject = rjson[mapType.c_str()];
        for (rapidjson::Value::ConstMemberIterator it = membersObject.MemberonBegin(); it != membersObject.MemberonEnd(); it++)
        {
            map.emplace(std::string(it->name.GetString()), std::string(it->value.GetString()));
        }
    }
}

void ResMgr::__initResMap(const ResType type, const rapidjson::Document& rjson)
{
    if (m_mapResType.find(type) != m_mapResType.end())
    {
        __initMapFromJson(std::get<0>(m_mapResType[type]), std::get<1>(m_mapResType[type]), rjson);
    }
}

void ResMgr::__getImgPath(const rapidjson::Document& rjson)
{
   if (rjson.IsObject() && rjson.HasMember("package_prefix"))
   {
       const rapidjson::Value& prefixArray = rjson["package_prefix"];
       CCASSERT(prefixArray.Size() == 1, "[ResMgr][__getImgPath]: prefixArray size != 1");
       m_sImgPathPrefix = prefixArray[SizeType(0)].GetString();
   }
}

cocos2d::Ref* ResMgr::__createSprite(const std::string& pStr)
{
    Ref* pRef = nullptr;
    if (__checkPathStr(ResType::kSprite, pStr))
    {
        pRef = Sprite::createWithSpriteFrameName(__getPathByKey(ResType::kSprite, pStr));
    } 
    else
    {
        pRef = Sprite::create(__getPathByKey(ResType::kSprite, pStr));
    }
    return pRef;
}

cocos2d::Ref* ResMgr::__createScale9Sprite(const std::string& pStr)
{
    Ref* pRef = nullptr;
    if (__checkPathStr(ResType::kScale9Sprite, pStr))
    {
        pRef = Scale9Sprite::createWithSpriteFrameName(__getPathByKey(ResType::kSprite, pStr));
    }
    else
    {
        pRef = Scale9Sprite::create(__getPathByKey(ResType::kSprite, pStr));
    }
    return pRef;
}

cocos2d::Ref* ResMgr::__createCsbLayer(const std::string& pStr)
{
    Ref* pRef = nullptr;
    auto pCSLoader = CSLoader::getInstance();
    pRef = pCSLoader->createNode(__getPathByKey(ResType::kCsb, pStr));
    return pRef;
}

cocos2d::GLProgramState* ResMgr::__createShaderProgram(const std::string& pVertexStr, const std::string& pFragStr)
{
    auto pVextexShaderPath = __getPathByKey(ResType::kShader, pVertexStr);
    auto pFragmentShaderPath = __getPathByKey(ResType::kShader, pFragStr);
    auto program = GLProgram::createWithFilenames(pVextexShaderPath, pFragmentShaderPath);
    return GLProgramState::getOrCreateWithGLProgram(program);
}

const std::string ResMgr::__getPathByKey(const ResType type, const std::string& key)
{
   if (m_mapResType.find(type) != m_mapResType.end())
   {
       auto map = std::get<1>(m_mapResType[type]);
       if (map.find(key) != map.end())
       {
           return map.at(key);
       }
       else
       {
           return "";
       }
   }
}