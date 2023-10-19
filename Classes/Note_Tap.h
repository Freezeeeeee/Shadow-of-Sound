#ifndef __GAME_TAP_H__
#define __GAME_TAP_H__

#include "cocos2d.h"

USING_NS_CC;

class Note : public cocos2d::Sprite
{
public:
    int Note_x;
    int Note_y;
    float Note_speed;
    Note(int x,int y,float speed);
    void Note_down();
    void Note_end();
    void Note_update(float dt);
};

#endif

