#ifndef __GAME_SET_H__
#define __GAME_SET_H__

#include "cocos2d.h"
#include "cocos-ext.h"          
using namespace cocos2d::extension;
#include "ui/CocosGUI.h"
using namespace rapidjson;

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;

class GameSet : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    rapidjson::Document RecJson;
    std::string Rec;

    void backmeun();

    void ValueChanged(Ref* sender, Control::EventType controlEvent);

    void EffectChanged(Ref* sender, Control::EventType controlEvent);

    CREATE_FUNC(GameSet);
};

#endif
