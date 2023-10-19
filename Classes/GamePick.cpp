#include "GamePick.h"
#include "MenuPick_1.h"
#include "MenuPick_2.h"
#include "MenuPick_3.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>
using namespace CocosDenshion;

USING_NS_CC;

std::string Diff;
std::string Filename;

Scene* GamePick::createScene()
{
	return GamePick::create();
}

bool GamePick::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	//背景
	auto Backlayer = LayerColor::create(Color4B::WHITE);
	this->addChild(Backlayer, 0, 0);
	auto Main_interface = Sprite::create("Picture/Pickbackground.png");
	Main_interface->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	Backlayer->addChild(Main_interface, 1);


	//菜单,layer的继承类
	auto Menuitem = Sprite::create("Picture/TextMeun 1.png");
	auto MenuItem1 = MenuItemSprite::create(Menuitem, Menuitem, Menuitem);
	MenuItem1->initWithCallback(CC_CALLBACK_1(GamePick::menupick_1, this));
	Menuitem = Sprite::create("Picture/TextMeun 2.png");
	auto MenuItem2 = MenuItemSprite::create(Menuitem, Menuitem, Menuitem,
		CC_CALLBACK_1(GamePick::menupick_2, this));
	Menuitem = Sprite::create("Picture/TextMeun 3.png");
	auto MenuItem3 = MenuItemSprite::create(Menuitem, Menuitem, Menuitem,
		CC_CALLBACK_1(GamePick::menupick_3, this));
	auto Menu = Menu::create(MenuItem1, MenuItem2, MenuItem3, NULL);
	//菜单初始设为Zero，菜单项设置的是相对位置
	Menu->setPosition(Vec2(0, 0));
	MenuItem1->setAnchorPoint(Vec2(0.5, 0.5));
	MenuItem2->setAnchorPoint(Vec2(0.5, 0.5));
	MenuItem3->setAnchorPoint(Vec2(0.5, 0.5));
	MenuItem2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	MenuItem1->setPosition(MenuItem2->getPosition() + Vec2(-600, 0));
	MenuItem3->setPosition(MenuItem2->getPosition() + Vec2(600, 0));
	this->addChild(Menu, 1, 1);

	// creating a keyboard event listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {

		if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			SimpleAudioEngine::getInstance()->playEffect("Music file/Pick.mp3");
		}

	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {

		if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			SimpleAudioEngine::getInstance()->playEffect("Music file/Pick.mp3"); 
			backmeun();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void GamePick::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void GamePick::backmeun()
{
	Director::getInstance()->popScene();
}

void GamePick::menupick_1(Ref* pSender)
{
	Scene* scene = MenuPick_1::createScene();
	Director::getInstance()->pushScene(TransitionFadeBL::create(1.5, scene));
}

void GamePick::menupick_2(Ref* pSender)
{
	Scene* scene = MenuPick_2::createScene();
	Director::getInstance()->pushScene(TransitionFadeBL::create(1.5, scene));
}

void GamePick::menupick_3(Ref* pSender)
{
	Scene* scene = MenuPick_3::createScene();
	Director::getInstance()->pushScene(TransitionFadeBL::create(1.5, scene));
}