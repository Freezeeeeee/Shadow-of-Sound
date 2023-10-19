#ifndef __MENU_3_H__
#define __MENU_3_H__
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;

class MenuPick_3 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    rapidjson::Document RecJson;
    int Pick_Music = 1;//����ѡ��
    int Pick_diff = 2;//�Ѷ�ѡ��
    std::string music_name = "Kibonoha -Uru";//����
    std::string Rec;

    virtual bool init();

    void pickdiffprer(int pick);//��ť�ص�ѡ�Ѷ�

    void pickspeed(int pick);//�����ٶ�

    void pickmusic(int pick);

    void pickdifficulty(float dt);//��ʱ��������

    void backmeun();

    void gameplay(Ref* pSender);//������Ϸ

    void restartplay(Ref* pSender);//�ؿ�

    char* MenuPick_3::FontToUTF8(const char* font);//��cocos2dx�ı�UTF8��������ʾ����

    CREATE_FUNC(MenuPick_3);
};

#endif