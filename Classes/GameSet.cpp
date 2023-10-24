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

	//��ɫ����
	auto SetBack = Sprite::create("Picture/Butt/Back_Volume.png");
	SetBack->setPosition(Vec2(visibleSize.width / 2, 820));
	this->addChild(SetBack, 1);

	auto SetEffect = Sprite::create("Picture/Butt/Back_Effect.png");
	SetEffect->setPosition(Vec2(visibleSize.width / 2, 570));
	this->addChild(SetEffect, 1);

	//������ʾSliderֵ�ı�ǩ
	Rec = FileUtils::getInstance()->getStringFromFile("Record/GameSet.json");
	RecJson.Parse<rapidjson::kParseDefaultFlags>(Rec.c_str());
	char str[10];
	sprintf(str, "%.1f", RecJson["MusicVolume"].GetFloat());

	auto label = Label::createWithTTF(str, "fonts/Saira-Thin.ttf", 36);
	label->setPosition(Vec2(visibleSize.width / 2, 765));
	this->addChild(label,2,1);


	//��������ؼ�ControlSlider
	auto slider = ControlSlider::create("Picture/Butt/Track.png", "Picture/Butt/Progress.png", 
		"Picture/Butt/Thumb.png");
	slider->setPosition(Vec2(1100, 820));
	this->addChild(slider,2,2);

	//��������
	slider->setMinimumValue(0);         //���û�����Сֵ
	slider->setMaximumValue(100);       //���û������ֵ
	slider->setMinimumAllowedValue(90);	//��������������Сֵ,���Ǹ����裬cocos2dx�ֳ����
	slider->setMaximumAllowedValue(100); //���������������ֵ
	slider->setValue(RecJson["MusicVolume"].GetFloat());//���õ�ǰ�����ֵ

	sprintf(str, "%.1f", RecJson["EffectVolume"].GetFloat());

	auto label_2 = Label::createWithTTF(str, "fonts/Saira-Thin.ttf", 36);
	label_2->setPosition(Vec2(visibleSize.width / 2, 515));
	this->addChild(label_2, 2, 3);


	//��������ؼ�ControlSlider
	auto Effect = ControlSlider::create("Picture/Butt/Track.png", "Picture/Butt/Progress.png",
		"Picture/Butt/Thumb.png");
	Effect->setPosition(Vec2(1100, 570));
	this->addChild(Effect, 2, 4);

	//��������
	Effect->setMinimumValue(0);         //���û�����Сֵ
	Effect->setMaximumValue(100);       //���û������ֵ
	Effect->setMinimumAllowedValue(0);	//��������������Сֵ
	Effect->setMaximumAllowedValue(100); //���������������ֵ
	Effect->setValue(RecJson["EffectVolume"].GetFloat());//���õ�ǰ�����ֵ


	//�ص�
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
	//�޸�����
	ControlSlider* slider = (ControlSlider*)this->getChildByTag(2);
	ControlSlider* Effect = (ControlSlider*)this->getChildByTag(4);
	SimpleAudioEngine::getInstance()->setEffectsVolume(Effect->getValue() / 100);
	//��json��������д���ļ���
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
	//�޸�label��ֵ����ʾ����ĵ�ǰֵ
	//sprintfΪC�����е��ַ�����ʽת�������ｫfloatת��Ϊ�ַ���
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


