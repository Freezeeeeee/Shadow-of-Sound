#include "HelloWorldScene.h"
#include "GamePick.h"
#include "GameSet.h"
#include "GameStastis.h"
#include "GameMyself.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>
using namespace CocosDenshion;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    // add a "close" icon to exit the progress. it's an autorelease object
    auto SetItem = MenuItemImage::create("Picture/Butt/Set.png","Picture/Butt/Set.png",
        CC_CALLBACK_1(HelloWorld::gameset, this));//设置
    auto StaItem = MenuItemImage::create("Picture/Butt/Statistics.png", "Picture/Butt/Statistics.png",
        CC_CALLBACK_1(HelloWorld::gamesta, this));//统计
    auto MyItem = MenuItemImage::create("Picture/Butt/Myself.png", "Picture/Butt/Myself.png",
        CC_CALLBACK_1(HelloWorld::gamemyself, this));//本人

    SetItem->setAnchorPoint(Vec2(1, 0));
    SetItem->setPosition(Vec2(visibleSize.width - 10, 10));
    StaItem->setAnchorPoint(Vec2(1, 0));
    StaItem->setPosition(Vec2(visibleSize.width - 80, 10));
    MyItem->setAnchorPoint(Vec2(1, 0));
    MyItem->setPosition(Vec2(visibleSize.width - 150, 10));

    // create menu, it's an autorelease object
    auto menu = Menu::create(SetItem, StaItem,MyItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // add a label shows "Press To Enter"
    // create and initialize a label and blink
    auto label = Label::createWithTTF("Press any key to enter", "fonts/Marker Felt.ttf", 36);
    label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/4 - 
        label->getContentSize().height));
    this->addChild(label, 1);
    //创建一个动画Fade
    auto fade_1 = FadeTo::create(1.0f, 0);
    auto fade_2 = FadeTo::create(1.0f, 255);
    auto blink = Sequence::create(fade_1, fade_2, NULL);
    auto blink_repeat = RepeatForever::create(blink);
    label->runAction(blink_repeat);


    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 - 60));

    // add the sprite as a child to this layer
    this->addChild(sprite, 1);

    //预加载音效
    SimpleAudioEngine::getInstance()->preloadEffect("Music file/Tap_Perfect.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("Music file/Tap_Good.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("Music file/Note_One.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("Music file/Note_Two.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("Music file/Pick.mp3");

    //主界面
    auto Main_interface = Sprite::create("Picture/Main interface.png", Rect(0, 0,
        GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)));
    Main_interface->setPosition( Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(Main_interface, 0);

    // creating a keyboard event listener
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
    };
    // Any key enter and Esc back
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
        {
            Director::getInstance()->end();
        }
        else
        {
            SimpleAudioEngine::getInstance()->playEffect("Music file/Pick.mp3");
            this->gamepick();
        }  
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}

void HelloWorld::gamepick()
{
    Scene* scene = GamePick::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.5, scene));
}

void HelloWorld::gameset(Ref* pSender)
{
    Scene* scene = GameSet::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.5, scene));
}

void HelloWorld::gamesta(Ref* pSender)
{
    Scene* scene = GameStastis::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.5, scene));
}

void HelloWorld::gamemyself(Ref* pSender)
{
    Scene* scene = GameMyself::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.5, scene));
}