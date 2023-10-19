#ifndef __GAME_PLAY_H__
#define __GAME_PLAY_H__

#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;

class GamePlay : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    //先延迟两秒，240帧数
    int Game_time = -240;//开始帧数计数，类内初始化C++11新特性
    float Play_speed = 0;//理论上讲应该支持变速的，不过我懒
    int Play_Perfect = 0;//四 大 类 型
    int Play_Good = 0;
    int Play_Pass = 0;
    int Play_Bad = 0;
    int Play_Combo = 0;//Combo数
    int Play_MaxCombo = 0;//最大Combo数
    int Play_Toatal = 0;//物量
    int Play_Score = 0;//分数
    int Play_GetScore = 0;//通过计算之后一次Perfect分数
    bool Play_Start = false;//开始播放音乐了吗
    bool Play_End = false;//结束了吗
    rapidjson::Document RecJson;//Json文件
    std::list<float> Game_file;//List读取文件相关

    virtual bool init();

    void menuCloseCallback(cocos2d::Ref* pSender);

    static void backmeun(Ref* pSender);//返回选歌界面
    void CreateNote(int time);//制造音符
    void Update_count(float dt);//定时器更新
    void Game_combo();//粒子特效
    void GamePre();//读取文件之类准备工作
    void GamePause(Ref* pSender);//暂停
    void PauseAfter();//暂停回调函数
    void GameEnd();//结束，进入结算界面
    CREATE_FUNC(GamePlay);
};

#endif