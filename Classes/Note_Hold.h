#ifndef __GAME_HOLD_H__
#define __GAME_HOLD_H__

#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"

USING_NS_CC;

//Holdʹ�þŹ������࣬�����ڲ�ȷ����������ʱ��������
class Hold : public cocos2d::ui::Scale9Sprite
{
public:
    int Hold_x;//���
    int Hold_y;//��ǰ����
    float Hold_speed;//�ٶ�
    int Hold_length;//�ܳ�
    int Hold_state = 0;//״̬
    int Hold_PorG = 0;//Perfect/Good
    int Music_number = 0;//��Ч���
    int Cycle = 0;//������Чѭ�����
    bool End = false;//������Ч�ж�
    Sprite* Icon;//������Ч����ָ��
    Hold(int x, int y, float speed);
    void Hold_down();
    void Hold_end();
    void Hold_update(float dt);
};

#endif