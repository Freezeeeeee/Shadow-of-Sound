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

    //���ӳ����룬240֡��
    int Game_time = -240;//��ʼ֡�����������ڳ�ʼ��C++11������
    float Play_speed = 0;//�����Ͻ�Ӧ��֧�ֱ��ٵģ���������
    int Play_Perfect = 0;//�� �� �� ��
    int Play_Good = 0;
    int Play_Pass = 0;
    int Play_Bad = 0;
    int Play_Combo = 0;//Combo��
    int Play_MaxCombo = 0;//���Combo��
    int Play_Toatal = 0;//����
    int Play_Score = 0;//����
    int Play_GetScore = 0;//ͨ������֮��һ��Perfect����
    bool Play_Start = false;//��ʼ������������
    bool Play_End = false;//��������
    rapidjson::Document RecJson;//Json�ļ�
    std::list<float> Game_file;//List��ȡ�ļ����

    virtual bool init();

    void menuCloseCallback(cocos2d::Ref* pSender);

    static void backmeun(Ref* pSender);//����ѡ�����
    void CreateNote(int time);//��������
    void Update_count(float dt);//��ʱ������
    void Game_combo();//������Ч
    void GamePre();//��ȡ�ļ�֮��׼������
    void GamePause(Ref* pSender);//��ͣ
    void PauseAfter();//��ͣ�ص�����
    void GameEnd();//����������������
    CREATE_FUNC(GamePlay);
};

#endif