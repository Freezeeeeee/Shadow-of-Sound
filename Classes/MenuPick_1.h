#ifndef __MENU_1_H__
#define __MENU_1_H__
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;

class MenuPick_1 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    rapidjson::Document RecJson;
    std::string Rec;

    int Pick_Music = 1;//����ѡ��
    int Pick_diff = 2;//�Ѷ�ѡ��
    std::string music_name = "Inferno City -Ponch";//����

    virtual bool init();

    void pickdiffprer(int pick);//��ť�ص�ѡ�Ѷ�

    void pickspeed(int pick);//�����ٶ�

    void pickmusic(int pick);

    void pickdifficulty(float dt);//��ʱ��������

    void backmeun();

    char* FontToUTF8(const char* font);//����ת��

    void gameplay(Ref* pSender);//������Ϸ

    void restartplay(Ref* pSender);//�ؿ�

    CREATE_FUNC(MenuPick_1);
};

#endif