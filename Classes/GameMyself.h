#ifndef __GAME_My_H__
#define __GAME_My_H__

#include "cocos2d.h"

USING_NS_CC;

class GameMyself : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void backmeun();

    CREATE_FUNC(GameMyself);
};

#endif