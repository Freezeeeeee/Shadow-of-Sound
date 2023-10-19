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

    rapidjson::Document RecJson;//Json�ļ�
    std::list<float> Game_file;//List��ȡ�ļ����

    virtual bool init();

    void Count_Level(std::string text);//ͳ������

    void backmeun();

    CREATE_FUNC(GameStastis);
};

#endif