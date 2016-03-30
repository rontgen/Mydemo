#include "ResMgr.h"
#include "CSLoader.h"
#include "rapidjson.h"

USING_NS_CC;
using namespace cocos2d::ui;
//ResMgr* ResMgr::m_sResMgr = nullptr;

ResMgr::ResMgr()
    : m_mapImages()
    , m_sImgPathPrefix("")
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
    if (rapidJson.HasParseError())  //解析错误  
    {
        log("GetParseError %s\n", rapidJson.GetParseError());
    }
    __getImgPath(rapidJson);
    __initResMap(kSprite, rapidJson);
    __initResMap(kCsb, rapidJson);
    __initResMap(kShader, rapidJson);
    return true;
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
    case kShader:
    {
        CCASSERT(m_mapShader.find(resKey) != m_mapShader.end(), "");
        return m_mapShader.at(resKey);
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
    case kShader:
    {
        if (rjson.IsObject() && rjson.HasMember("shader"))
        {
            const rapidjson::Value& membersObject = rjson["shader"];
            for (rapidjson::Value::ConstMemberIterator it = membersObject.MemberonBegin(); it != membersObject.MemberonEnd(); it++)
            {
                m_mapShader.insert(std::make_pair(std::string(it->name.GetString()), std::string(it->value.GetString())));
            }
        }
    }
    break;
    default:
        break;
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
    return pRef;
}

cocos2d::GLProgramState* ResMgr::__createShaderProgram(const std::string& pVertexStr, const std::string& pFragStr)
{
    auto pVextexShaderPath = __getPathByKey(ResType::kShader, pVertexStr);
    auto pFragmentShaderPath = __getPathByKey(ResType::kShader, pFragStr);
    auto program = GLProgram::createWithFilenames(pVextexShaderPath, pFragmentShaderPath);
    return GLProgramState::getOrCreateWithGLProgram(program);
}

const std::string& ResMgr::__getPathByKey(const ResType type, const std::string& key)
{
    
    switch (type)
    {
    case kSprite:
    {
        if (m_mapImages.find(key)!= m_mapImages.end())
        {
            return m_mapImages.at(key);
        }
        else
        {
            return "";
        }
    }
    break;
    case kCsb:
    {
        if (m_mapLayout.find(key) != m_mapLayout.end())
        {
            return m_mapLayout.at(key);
        }
        else
        {
            return "";
        }
    }
    case kShader:
    {
        if (m_mapShader.find(key) != m_mapShader.end())
        {
            return m_mapShader.at(key);
        }
        else
        {
            return "";
        }
    }
    break;
    default:
        break;
    }
}