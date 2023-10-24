#include "GameMyself.h"

USING_NS_CC;

Scene* GameMyself::createScene()
{
	return GameMyself::create();
}

bool GameMyself::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto BackGround = Sprite::create("Picture/Myself interface.png");
	BackGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(BackGround, 1);


	// creating a keyboard event listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			backmeun();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}


void GameMyself::backmeun()
{
	Director::getInstance()->popScene();
}