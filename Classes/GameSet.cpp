#include "GameSet.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>
using namespace CocosDenshion;
using namespace ui;

USING_NS_CC;

Scene* GameSet::createScene()
{
	return GameSet::create();
}

bool GameSet::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto BackGround = Sprite::create("Picture/Set interface.png");
	BackGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(BackGround, 1);

	//蓝色背景
	auto SetBack = Sprite::create("Picture/Butt/Back_Volume.png");
	SetBack->setPosition(Vec2(visibleSize.width / 2, 820));
	this->addChild(SetBack, 1);

	auto SetEffect = Sprite::create("Picture/Butt/Back_Effect.png");
	SetEffect->setPosition(Vec2(visibleSize.width / 2, 570));
	this->addChild(SetEffect, 1);

	//创建显示Slider值的标签
	Rec = FileUtils::getInstance()->getStringFromFile("Record/GameSet.json");
	RecJson.Parse<rapidjson::kParseDefaultFlags>(Rec.c_str());
	char str[10];
	sprintf(str, "%.1f", RecJson["MusicVolume"].GetFloat());

	auto label = Label::createWithTTF(str, "fonts/Saira-Thin.ttf", 36);
	label->setPosition(Vec2(visibleSize.width / 2, 765));
	this->addChild(label,2,1);


	//创建滑块控件ControlSlider
	auto slider = ControlSlider::create("Picture/Butt/Track.png", "Picture/Butt/Progress.png", 
		"Picture/Butt/Thumb.png");
	slider->setPosition(Vec2(1100, 820));
	this->addChild(slider,2,2);

	//设置属性
	slider->setMinimumValue(0);         //设置滑块最小值
	slider->setMaximumValue(100);       //设置滑块最大值
	slider->setMinimumAllowedValue(90);	//设置允许滑动的最小值,这是个摆设，cocos2dx又抽风了
	slider->setMaximumAllowedValue(100); //设置允许滑动的最大值
	slider->setValue(RecJson["MusicVolume"].GetFloat());//设置当前滑块的值

	sprintf(str, "%.1f", RecJson["EffectVolume"].GetFloat());

	auto label_2 = Label::createWithTTF(str, "fonts/Saira-Thin.ttf", 36);
	label_2->setPosition(Vec2(visibleSize.width / 2, 515));
	this->addChild(label_2, 2, 3);


	//创建滑块控件ControlSlider
	auto Effect = ControlSlider::create("Picture/Butt/Track.png", "Picture/Butt/Progress.png",
		"Picture/Butt/Thumb.png");
	Effect->setPosition(Vec2(1100, 570));
	this->addChild(Effect, 2, 4);

	//设置属性
	Effect->setMinimumValue(0);         //设置滑块最小值
	Effect->setMaximumValue(100);       //设置滑块最大值
	Effect->setMinimumAllowedValue(0);	//设置允许滑动的最小值
	Effect->setMaximumAllowedValue(100); //设置允许滑动的最大值
	Effect->setValue(RecJson["EffectVolume"].GetFloat());//设置当前滑块的值


	//回调
	slider->addTargetWithActionForControlEvents(this, cccontrol_selector(GameSet::ValueChanged),
		Control::EventType::VALUE_CHANGED);

	Effect->addTargetWithActionForControlEvents(this, cccontrol_selector(GameSet::EffectChanged),
		Control::EventType::VALUE_CHANGED);

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

void GameSet::backmeun()
{
	//修改音量
	ControlSlider* slider = (ControlSlider*)this->getChildByTag(2);
	ControlSlider* Effect = (ControlSlider*)this->getChildByTag(4);
	SimpleAudioEngine::getInstance()->setEffectsVolume(Effect->getValue() / 100);
	//将json数据重新写入文件中
	RecJson["MusicVolume"].SetFloat(slider->getValue());
	RecJson["EffectVolume"].SetFloat(Effect->getValue());
	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	RecJson.Accept(writer);
	FILE* Readfile = fopen("Resources/Record/GameSet.json", "wb");
	fputs(buffer.GetString(), Readfile);
	fclose(Readfile);
	Director::getInstance()->popScene();
}

void GameSet::ValueChanged(Ref* sender, Control::EventType controlEvent)
{
	ControlSlider* slider = (ControlSlider*)sender;
	//修改label的值，显示滑块的当前值
	//sprintf为C语言中的字符串格式转换，这里将float转换为字符串
	char str[10];
	sprintf(str, "%.1f", slider->getValue());
	auto lable = (Label*)this->getChildByTag(1);
	lable->setString(str);
}

void GameSet::EffectChanged(Ref* sender, Control::EventType controlEvent)
{
	ControlSlider* slider = (ControlSlider*)sender;
	char str[10];
	sprintf(str, "%.1f", slider->getValue());
	auto lable = (Label*)this->getChildByTag(3);
	lable->setString(str);
}


