#include "GameStastis.h"

USING_NS_CC;

int Ez_count[3];
int Hd_count[3];
int In_count[3];

Scene* GameStastis::createScene()
{
	return GameStastis::create();
}

bool GameStastis::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto BackGround = Sprite::create("Picture/Stastis interface.png");
	BackGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(BackGround, 1);

	Count_Level("Escaping Gravity -TheFatRat");
	Count_Level("Unity -TheFatRat");
	Count_Level("The Calling -TheFatRat");
	Count_Level("Monody(1) -TheFatRat");
	Count_Level("Monody(2) -TheFatRat");
	Count_Level("Xenogenesis -TheFatRat");
	Count_Level("Never Be Alone -TheFatRat");
	Count_Level("Mayday -TheFatRat");
	Count_Level("Spring Shadow -MyGo");
	Count_Level("For the Damaged Coda -Rick and Morty");
	Count_Level("Bad Apple -TouHou");
	Count_Level("Only My Railgun -Super Gun");
	Count_Level("Number One -Bleach");
	Count_Level("Senbonzakura -Lindsey Stirling");
	Count_Level("La Campanella - SunsetRay");
	Count_Level("Inferno City -Ponch");
	Count_Level("Jack War -YGO5ds");
	Count_Level("Bella Ciao -Kaiserreich");
	Count_Level("La Marseillaise -French national anthem");
	Count_Level("Kibonoha -Uru");


	char Temporary[32];
	//蓝色背景
	auto StaBack = Sprite::create("Picture/Butt/StaBack.png");
	StaBack->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(StaBack, 1);
	//Ez
	auto Ez_visible = Label::createWithTTF("Ez", "fonts/simhei.ttf", 72);
	this->addChild(Ez_visible, 1);
	Ez_visible->setPosition(Vec2(400, 760));
	sprintf(Temporary, "Ap:%d/22    Fc:%d/22    S:%d/22", Ez_count[0], Ez_count[1], Ez_count[2]);
	auto Ez_cutt = Label::createWithTTF(Temporary, "fonts/simhei.ttf", 64);
	this->addChild(Ez_cutt, 1);
	Ez_cutt->setPosition(Vec2(1050, 760));
	//Hd
	auto Hd_visible = Label::createWithTTF("Hd", "fonts/simhei.ttf", 72);
	this->addChild(Hd_visible, 1);
	Hd_visible->setPosition(Vec2(400, 540));
	sprintf(Temporary, "Ap:%d/22    Fc:%d/22    S:%d/22", Hd_count[0], Hd_count[1], Hd_count[2]);
	auto Hd_cutt = Label::createWithTTF(Temporary, "fonts/simhei.ttf", 64);
	this->addChild(Hd_cutt, 1);
	Hd_cutt->setPosition(Vec2(1050, 540));
	//In
	auto In_visible = Label::createWithTTF("In", "fonts/simhei.ttf", 72);
	this->addChild(In_visible, 1);
	In_visible->setPosition(Vec2(400, 320));
	sprintf(Temporary, "Ap:%d/22    Fc:%d/22    S:%d/22", In_count[0], In_count[1], In_count[2]);
	auto In_cutt = Label::createWithTTF(Temporary, "fonts/simhei.ttf", 64);
	this->addChild(In_cutt, 1);
	In_cutt->setPosition(Vec2(1050, 320));

	Ez_cutt->setOpacity(0);
	Hd_cutt->setOpacity(0);
	In_cutt->setOpacity(0);
	auto fade = FadeTo::create(1.0f, 255);
	auto delay = DelayTime::create(1.0f);
	auto Appear_1 = Sequence::create(delay, fade, NULL);
	auto Appear_2 = Sequence::create(delay, delay, fade, NULL);
	auto Appear_3 = Sequence::create(delay, delay, delay, fade, NULL);
	Ez_cutt->runAction(Appear_1);
	Hd_cutt->runAction(Appear_2);
	In_cutt->runAction(Appear_3);

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


void GameStastis::backmeun()
{
	Director::getInstance()->popScene();
}

void GameStastis::Count_Level(std::string text)
{
	//读取Json文件
	static std::string Rec = FileUtils::getInstance()->getStringFromFile("Record/GameRecord.json");
	RecJson.Parse<rapidjson::kParseDefaultFlags>(Rec.c_str());
	if (RecJson[text.c_str()]["Level"]["Ez"] == "S")
	{
		Ez_count[2]++;
	}
	else if (RecJson[text.c_str()]["Level"]["Ez"] == "Fc")
	{
		Ez_count[1]++;
		Ez_count[2]++;
	}
	else if (RecJson[text.c_str()]["Level"]["Ez"] == "Ap")
	{
		Ez_count[0]++;
		Ez_count[1]++;
		Ez_count[2]++;
	}
	if (RecJson[text.c_str()]["Level"]["Hd"] == "S")
	{
		Hd_count[2]++;
	}
	else if (RecJson[text.c_str()]["Level"]["Hd"] == "Fc")
	{
		Hd_count[1]++;
		Hd_count[2]++;
	}
	else if (RecJson[text.c_str()]["Level"]["Hd"] == "Ap")
	{
		Hd_count[0]++;
		Hd_count[1]++;
		Hd_count[2]++;
	}
	if (RecJson[text.c_str()]["Level"]["In"] == "S")
	{
		In_count[2]++;
	}
	else if (RecJson[text.c_str()]["Level"]["In"] == "Fc")
	{
		In_count[1]++;
		In_count[2]++;
	}
	else if (RecJson[text.c_str()]["Level"]["In"] == "Ap")
	{
		In_count[0]++;
		In_count[1]++;
		In_count[2]++;
	}
}
