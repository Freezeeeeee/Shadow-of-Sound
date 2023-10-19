#ifndef __GAME_PICK_H__
#define __GAME_PICK_H__

#include "cocos2d.h"

USING_NS_CC;

class GamePick : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuCloseCallback(cocos2d::Ref* pSender);

    void backmeun();

    void menupick_1(Ref* pSender);

    void menupick_2(Ref* pSender);

    void menupick_3(Ref* pSender);

    CREATE_FUNC(GamePick);
};

#endif
