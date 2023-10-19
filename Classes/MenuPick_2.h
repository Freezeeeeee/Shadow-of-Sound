#ifndef __MENU_2_H__
#define __MENU_2_H__
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;

class MenuPick_2 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    rapidjson::Document RecJson;
    int Pick_Music = 1;//歌曲选择
    int Pick_diff = 2;//难度选择
    std::string music_name = "Escaping Gravity -TheFatRat";//歌名
    std::string Rec;

    virtual bool init();

    void pickdiffprer(int pick);//按钮回调选难度

    void pickspeed(int pick);//调节速度

    void pickmusic(int pick);

    void pickdifficulty(float dt);//定时器个更新
    
    void backmeun();

    char* FontToUTF8(const char* font);

    void gameplay(Ref* pSender);//进入游戏

    void restartplay(Ref* pSender);//重开

    CREATE_FUNC(MenuPick_2);
};

#endif