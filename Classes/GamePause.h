#ifndef __GAME_PICK_H__
#define __GAME_PICK_H__

#include "cocos2d.h"

USING_NS_CC;

class GamePause : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(RenderTexture* sqr);

    virtual bool init();

    void back_pick(Ref* pSender);

    void game_restart(Ref* pSender);

    void pause_continue(Ref* pSender);

    

    CREATE_FUNC(GamePause);
};

#endif
