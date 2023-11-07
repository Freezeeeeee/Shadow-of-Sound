#include "StartScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    return StartScene::create();
}

bool StartScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //黑色背景
    auto Background = LayerColor::create(Color4B::BLACK);
    this->addChild(Background, 1);

    //精灵
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 60));
    sprite->setOpacity(0);
    sprite->runAction(Sequence::create(FadeIn::create(1.5f), NULL));
    this->addChild(sprite, 2);

    //文本
    auto Maker = Label::createWithTTF("Made by", "fonts/Saira-Regular.ttf", 72);
    Maker->setTextColor(Color4B::WHITE);
    Maker->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 300));
    Maker->setOpacity(0);
    Maker->runAction(Sequence::create(DelayTime::create(1.0f),FadeIn::create(2.0f),
        FadeOut::create(0.5f), NULL));
    this->addChild(Maker, 2);

    auto Szha = Label::createWithTTF("Szha", "fonts/Saira-Regular.ttf", 48);
    Szha->setTextColor(Color4B::WHITE);
    Szha->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 150));
    Szha->setOpacity(0);
    Szha->runAction(Sequence::create(DelayTime::create(1.5f), FadeIn::create(1.5f),
        FadeOut::create(0.5f), NULL));
    this->addChild(Szha, 2);

    auto Delay = DelayTime::create(3.5f);
    this->runAction(Sequence::create(Delay, CallFunc::
        create(CC_CALLBACK_0(StartScene::TransHello, this)), NULL));

    return true;
}

void StartScene::TransHello()
{
    Scene* scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(1.5, scene));
}