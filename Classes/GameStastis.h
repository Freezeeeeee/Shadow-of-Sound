#ifndef __GAME_STA_H__
#define __GAME_STA_H__

#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;

class GameStastis : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    rapidjson::Document RecJson;//Json文件
    std::list<float> Game_file;//List读取文件相关

    virtual bool init();

    void Count_Level(std::string text);//统计数据

    void backmeun();

    CREATE_FUNC(GameStastis);
};

#endif