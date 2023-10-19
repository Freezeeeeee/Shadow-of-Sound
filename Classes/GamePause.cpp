#include "GamePause.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>
using namespace CocosDenshion;

USING_NS_CC;

extern bool Play_TimeStop;
extern bool Play_TimeResume;
extern int PLay_Back;

Scene* GamePause::createScene(RenderTexture* sqr)
{
	//暂停时截个图片
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto PauseScene = GamePause::create();
	auto pauselayer = LayerColor::create();
	PauseScene->addChild(pauselayer);

	auto _spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	_spr->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	_spr->setFlippedY(true);
	
	pauselayer->addChild(_spr);
	return PauseScene;
}

bool GamePause::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto Pause_interface = Sprite::create("Cover/Pause.png");
	Pause_interface->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(Pause_interface, 1);

	//三个按钮
	auto Menuitem = Sprite::create("Cover/Pause_Left.png");
	auto MenuItem1 = MenuItemSprite::create(Menuitem, Menuitem, Menuitem);
	MenuItem1->initWithCallback(CC_CALLBACK_1(GamePause::back_pick, this));

	Menuitem = Sprite::create("Cover/Pause_Mid.png");
	auto MenuItem2 = MenuItemSprite::create(Menuitem, Menuitem, Menuitem,
		CC_CALLBACK_1(GamePause::game_restart, this));

	Menuitem = Sprite::create("Cover/Pause_Right.png");
	auto MenuItem3 = MenuItemSprite::create(Menuitem, Menuitem, Menuitem,
		CC_CALLBACK_1(GamePause::pause_continue, this));

	auto Menu = Menu::create(MenuItem1, MenuItem2, MenuItem3, NULL);
	MenuItem1->setPosition(Vec2(-180, 0));
	MenuItem2->setPosition(Vec2(0, 0));
	MenuItem3->setPosition(Vec2(180, 0));
	this->addChild(Menu, 2);

	// creating a keyboard event listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {

	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			pause_continue(this);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	return true;
}

void GamePause::back_pick(Ref* pSender)
{
	PLay_Back = 1;
	Director::getInstance()->popScene();
}

void GamePause::game_restart(Ref* pSender)
{
	PLay_Back = 2;
	Director::getInstance()->popScene();
}

void GamePause::pause_continue(Ref* pSender)
{
	Play_TimeResume = true;
	Director::getInstance()->popScene();
}


