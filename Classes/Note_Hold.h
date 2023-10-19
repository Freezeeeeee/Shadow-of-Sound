#ifndef __GAME_HOLD_H__
#define __GAME_HOLD_H__

#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"

USING_NS_CC;

//Hold使用九宫格精灵类，这样在不确定音符长度时很有作用
class Hold : public cocos2d::ui::Scale9Sprite
{
public:
    int Hold_x;//轨道
    int Hold_y;//当前长度
    float Hold_speed;//速度
    int Hold_length;//总长
    int Hold_state = 0;//状态
    int Hold_PorG = 0;//Perfect/Good
    int Music_number = 0;//音效编号
    int Cycle = 0;//粒子特效循环相关
    bool End = false;//动作特效判定
    Sprite* Icon;//动作特效精灵指针
    Hold(int x, int y, float speed);
    void Hold_down();
    void Hold_end();
    void Hold_update(float dt);
};

#endif