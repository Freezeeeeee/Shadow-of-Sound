#include "MenuPick_2.h"
#include "GamePlay.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>
using namespace CocosDenshion;
using namespace rapidjson;

USING_NS_CC;

extern std::string Diff;
extern std::string Filename;
extern int PLay_Back;
extern float Play_Sp;

Scene* MenuPick_2::createScene()
{
	return MenuPick_2::create();
}

bool MenuPick_2::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	//读取Json文件
	std::string Rec = FileUtils::getInstance()->getStringFromFile("Record/GameRecord.json");
	RecJson.Parse<rapidjson::kParseDefaultFlags>(Rec.c_str());
	//还是加了个计时器
	this->schedule(CC_SCHEDULE_SELECTOR(MenuPick_2::pickdifficulty));

	auto Backlayer = LayerColor::create(Color4B::BLACK);
	//Backlayer,tag 0,菜单tag 1,难度选择tag 2,选择单选tag 3,分数tag 4,难度tag 5,等级tag 6,歌曲图像tag7
	//箭头tag8
	this->addChild(Backlayer, 0, 0);
	auto Main_interface = Sprite::create("Cover/TheFatRat.png");
	Main_interface->setOpacity(100);
	Main_interface->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	Backlayer->addChild(Main_interface, 1);
	//歌曲选项

	auto White1 = Sprite::create("Cover/White.png");
	auto MenuPick1 = MenuItemSprite::create(White1, White1,
		CC_CALLBACK_0(MenuPick_2::pickmusic, this, 1));
	//曲名加到精灵上
	auto Pick1 = Label::createWithTTF("Escaping Gravity", "fonts/arial.ttf", 36);
	//Pick1->setColor(Color3B::BLACK);
	//Pick1->enableGlow(Color4B::RED);
	MenuPick1->addChild(Pick1, 0);
	Pick1->setPosition(Vec2(199, 29));

	//既然上边有格式了
	auto White2 = Sprite::create("Cover/White.png");
	auto MenuPick2 = MenuItemSprite::create(White2, White2,
		CC_CALLBACK_0(MenuPick_2::pickmusic, this, 2));
	auto Pick2 = Label::createWithTTF("Unity", "fonts/arial.ttf", 36);
	MenuPick2->addChild(Pick2, 0);
	Pick2->setPosition(Vec2(199, 29));

	auto White3 = Sprite::create("Cover/White.png");
	auto MenuPick3 = MenuItemSprite::create(White3, White3,
		CC_CALLBACK_0(MenuPick_2::pickmusic, this, 3));
	auto Pick3 = Label::createWithTTF("Monody 1 Part", "fonts/arial.ttf", 36);
	MenuPick3->addChild(Pick3, 0);
	Pick3->setPosition(Vec2(199, 29));

	auto White4 = Sprite::create("Cover/White.png");
	auto MenuPick4 = MenuItemSprite::create(White4, White4,
		CC_CALLBACK_0(MenuPick_2::pickmusic, this, 4));
	auto Pick4 = Label::createWithTTF("The Calling", "fonts/arial.ttf", 36);
	MenuPick4->addChild(Pick4, 0);
	Pick4->setPosition(Vec2(199, 29));

	auto White5 = Sprite::create("Cover/White.png");
	auto MenuPick5 = MenuItemSprite::create(White5, White5,
		CC_CALLBACK_0(MenuPick_2::pickmusic, this, 5));
	auto Pick5 = Label::createWithTTF("Monody 2 Part", "fonts/arial.ttf", 36);
	MenuPick5->addChild(Pick5, 0);
	Pick5->setPosition(Vec2(199, 29));

	auto White6 = Sprite::create("Cover/White.png");
	auto MenuPick6 = MenuItemSprite::create(White6, White6,
		CC_CALLBACK_0(MenuPick_2::pickmusic, this, 6));
	auto Pick6 = Label::createWithTTF("Xenogenesis", "fonts/arial.ttf", 36);
	MenuPick6->addChild(Pick6, 0);
	Pick6->setPosition(Vec2(199, 29));

	auto White7 = Sprite::create("Cover/White.png");
	auto MenuPick7 = MenuItemSprite::create(White7, White7,
		CC_CALLBACK_0(MenuPick_2::pickmusic, this, 7));
	auto Pick7 = Label::createWithTTF("Never Be Alone", "fonts/arial.ttf", 36);
	MenuPick7->addChild(Pick7, 0);
	Pick7->setPosition(Vec2(199, 29));

	auto White8 = Sprite::create("Cover/White.png");
	auto MenuPick8 = MenuItemSprite::create(White8, White8,
		CC_CALLBACK_0(MenuPick_2::pickmusic, this, 8));
	auto Pick8 = Label::createWithTTF("Mayday", "fonts/arial.ttf", 36);
	MenuPick8->addChild(Pick8, 0);
	Pick8->setPosition(Vec2(199, 29));

	//菜单
	auto Menu = Menu::create(MenuPick1, MenuPick2, MenuPick3, MenuPick4, MenuPick5, 
		MenuPick6, MenuPick7, MenuPick8, NULL);
	Menu->setPosition(Vec2(0, 0));
	MenuPick1->setPosition(Vec2(300, 900));
	MenuPick2->setPosition(Vec2(300, 800));
	MenuPick3->setPosition(Vec2(300, 700));
	MenuPick4->setPosition(Vec2(300, 600));
	MenuPick5->setPosition(Vec2(300, 500));
	MenuPick6->setPosition(Vec2(300, 400));
	MenuPick7->setPosition(Vec2(300, 300));
	MenuPick8->setPosition(Vec2(300, 200));
	this->addChild(Menu, 1, 1);

	/*歌曲的背景
	auto BackGround = Sprite::create("Cover/BackGround.png");
	BackGround->setOpacity(120);
	BackGround->setPosition(Vec2(visibleSize.width / 2 + 400, visibleSize.height / 2));
	this->addChild(BackGround, 2);*/
	//难度选择
	auto BackGround = Sprite::create("Cover/Difficulty.png");
	BackGround->setAnchorPoint(Vec2(0, 1));
	BackGround->setPosition(Vec2(visibleSize.width / 2 + 16, visibleSize.height / 2 - 230));
	this->addChild(BackGround, 2, 2);
	//初始Hd难度
	auto Pick_diff = Sprite::create("Cover/Hd2.png");
	this->addChild(Pick_diff, 4, 3);
	Pick_diff->setPosition(BackGround->getPosition() + Vec2(110, -25));
	//等级分数和难度
	auto GameLevel = Label::createWithTTF(" ", "fonts/arial.ttf", 48);
	this->addChild(GameLevel, 4, 6);
	GameLevel->setAnchorPoint(Vec2(0, 0.5));
	GameLevel->setPosition(Pick_diff->getPosition() + Vec2(595, 0));
	auto GameScore = Label::createWithTTF("0000000", "fonts/Saira-Light.ttf", 48);
	//GameScore->setAdditionalKerning(5);
	this->addChild(GameScore, 4, 4);
	GameScore->setAnchorPoint(Vec2(0, 0.5));
	GameScore->setPosition(Pick_diff->getPosition() + Vec2(265, 0));
	auto GameDiff = Label::createWithTTF("Lv.0", "fonts/arial.ttf", 36);
	this->addChild(GameDiff, 4, 5);
	GameDiff->setAnchorPoint(Vec2(0, 0.5));
	GameDiff->setPosition(Pick_diff->getPosition() + Vec2(125, 0));

	//速度
	auto Speed = Sprite::create("Cover/Butt/Speed.png");
	Speed->setAnchorPoint(Vec2(0, 1));
	Speed->setPosition(BackGround->getPosition() + Vec2(0, -80));
	this->addChild(Speed, 3);
	auto Sp_Left = MenuItemImage::create("Cover/Butt/Speed_Left.png", "Cover/Butt/Speed_Left.png",
		CC_CALLBACK_0(MenuPick_2::pickspeed, this, 1));
	auto Sp_Right = MenuItemImage::create("Cover/Butt/Speed_Right.png", "Cover/Butt/Speed_Right.png",
		CC_CALLBACK_0(MenuPick_2::pickspeed, this, 2));
	Sp_Left->setAnchorPoint(Vec2(0, 0));
	Sp_Right->setAnchorPoint(Vec2(1, 0));
	auto SpeedPick = Menu::create(Sp_Left, Sp_Right, NULL);
	SpeedPick->setPosition(Vec2(0, 0));
	Sp_Left->setPosition(Speed->getPosition() + Vec2(0, -50));
	Sp_Right->setPosition(Speed->getPosition() + Vec2(100, -50));
	this->addChild(SpeedPick, 3);
	//显示速度文本
	auto GameSp = Label::createWithTTF(" ", "fonts/Saira-Light.ttf", 20);
	GameSp->setColor(Color3B::BLACK);
	GameSp->setPosition(Speed->getPosition() + Vec2(50, -33));
	this->addChild(GameSp, 3, 9);

	//CC_CALLBACK_X中的参数
	//第一个是要回调的方法名称，用类名加方法的形式，
	//第二个参数是函数被调用的对象的指针，一般是this。
	//0是代表要回调的方法绑定第0个参数之后的参数。
	auto Ez_Diff = MenuItemImage::create("Cover/Ez1.png", "Cover/Ez1.png",
		CC_CALLBACK_0(MenuPick_2::pickdiffprer, this, 1));
	auto Hd_Diff = MenuItemImage::create("Cover/Hd1.png", "Cover/Hd1.png",
		CC_CALLBACK_0(MenuPick_2::pickdiffprer, this, 2));
	auto In_Diff = MenuItemImage::create("Cover/In1.png", "Cover/In1.png",
		CC_CALLBACK_0(MenuPick_2::pickdiffprer, this, 3));
	auto Difficluty = Menu::create(Ez_Diff, Hd_Diff, In_Diff, NULL);
	Difficluty->setPosition(Vec2(0, 0));
	Ez_Diff->setPosition(BackGround->getPosition() + Vec2(25, -25));
	Hd_Diff->setPosition(Ez_Diff->getPosition() + Vec2(85, 0));
	In_Diff->setPosition(Hd_Diff->getPosition() + Vec2(85, 0));
	this->addChild(Difficluty, 3);

	//歌曲作画
	auto PickSprite1 = Sprite::create("Cover/" + music_name+".png");
	PickSprite1->setScale(0.4);
	PickSprite1->setPosition(Vec2(visibleSize.width / 2 + 400, visibleSize.height / 2));
	this->addChild(PickSprite1, 3,7);

	//箭头
	auto Pick_Arrow = Sprite::create("Cover/Arrow.png");
	this->addChild(Pick_Arrow, 3, 8);
	Pick_Arrow->setAnchorPoint(Vec2(0, 0.5));
	Pick_Arrow->setPosition(MenuPick1->getPosition() + Vec2(215, 0));

	//进入按钮,独立于其他菜单项
	auto Enter = MenuItemImage::create("Cover/Enter.png", "Cover/Enter2.png", "Cover/Enter.png",
		CC_CALLBACK_1(MenuPick_2::gameplay, this));
	auto EnterMenu = Menu::create(Enter, NULL);
	EnterMenu->setPosition(Vec2(0, 0));
	Enter->setAnchorPoint(Vec2(1, 0));
	Enter->setPosition(Vec2(visibleSize.width - 1, 0));
	this->addChild(EnterMenu, 1);


	// creating a keyboard event listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {

		if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			SimpleAudioEngine::getInstance()->playEffect("Music file/Pick.mp3");
			MenuPick_2::gameplay(this);
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

void MenuPick_2::pickmusic(int pick)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto pickarrow = (Sprite*)this->getChildByTag(8);
	this->getChildByTag(7)->removeFromParentAndCleanup(true);

	if (pick == 1)
	{
		music_name = "Escaping Gravity -TheFatRat";
		pickarrow->setPosition(Vec2(515, 900));
	}
	else if (pick == 2)
	{
		music_name = "Unity -TheFatRat";
		pickarrow->setPosition(Vec2(515, 800));
	}
	else if (pick == 3)
	{
		music_name = "Monody(1) -TheFatRat";
		pickarrow->setPosition(Vec2(515, 700));
	}
	else if (pick == 4)
	{
		music_name = "The Calling -TheFatRat";
		pickarrow->setPosition(Vec2(515, 600));
	}
	else if (pick == 5)
	{
		music_name = "Monody(2) -TheFatRat";
		pickarrow->setPosition(Vec2(515, 500));
	}
	else if (pick == 6)
	{
		music_name = "Xenogenesis -TheFatRat";
		pickarrow->setPosition(Vec2(515, 400));
	}
	else if (pick == 7)
	{
		music_name = "Never Be Alone -TheFatRat";
		pickarrow->setPosition(Vec2(515, 300));
	}
	else if (pick == 8)
	{
		music_name = "Mayday -TheFatRat";
		pickarrow->setPosition(Vec2(515, 200));
	}
	auto PickSprite1 = Sprite::create("Cover/" + music_name + ".png");
	PickSprite1->setScale(0.4);
	PickSprite1->setPosition(Vec2(visibleSize.width / 2 + 400, visibleSize.height / 2));
	this->addChild(PickSprite1, 3, 7);
}

void MenuPick_2::pickspeed(int pick)
{
	Rec = FileUtils::getInstance()->getStringFromFile("Record/GameSet.json");
	RecJson.Parse<rapidjson::kParseDefaultFlags>(Rec.c_str());
	if (pick == 1 && Play_Sp > 1.05)
	{
		float Speed = Play_Sp - 0.1f;
		RecJson["Speed"].SetFloat(Speed);
	}
	if (pick == 2 && Play_Sp < 2.95)
	{
		float Speed = Play_Sp + 0.1f;
		RecJson["Speed"].SetFloat(Speed);
	}
	//将json数据重新写入文件中
	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	RecJson.Accept(writer);
	//不知道为什么在这cocos2d-x不能直接用相对路径
	std::string filepath = FileUtils::getInstance()->fullPathForFilename("Record/GameSet.json");
	FILE* Readfile = fopen(filepath.c_str(), "wb");
	fputs(buffer.GetString(), Readfile);
	fclose(Readfile);
}

void MenuPick_2::pickdiffprer(int pick)
{
	Pick_diff = pick;
	auto background = (Sprite*)this->getChildByTag(2);
	this->getChildByTag(3)->removeFromParentAndCleanup(true);
	if (Pick_diff == 1)
	{
		auto Pick_diff = Sprite::create("Cover/Ez2.png");
		this->addChild(Pick_diff, 4, 3);
		Pick_diff->setPosition(background->getPosition() + Vec2(25, -25));
	}
	else if (Pick_diff == 2)
	{
		auto Pick_diff = Sprite::create("Cover/Hd2.png");
		this->addChild(Pick_diff, 4, 3);
		Pick_diff->setPosition(background->getPosition() + Vec2(110, -25));
	}
	else if (Pick_diff == 3)
	{
		auto Pick_diff = Sprite::create("Cover/In2.png");
		this->addChild(Pick_diff, 4, 3);
		Pick_diff->setPosition(background->getPosition() + Vec2(195, -25));
	}
}

//更新
void MenuPick_2::pickdifficulty(float dt)
{
	Rec = FileUtils::getInstance()->getStringFromFile("Record/GameRecord.json");
	RecJson.Parse<rapidjson::kParseDefaultFlags>(Rec.c_str());

	auto background = (Sprite*)this->getChildByTag(2);

	auto gamescore = (Label*)this->getChildByTag(4);
	auto gamediff = (Label*)this->getChildByTag(5);
	auto gameLevel = (Label*)this->getChildByTag(6);
	char Temporary[32];

	if (Pick_diff == 1)
	{
		sprintf(Temporary, "%08d", RecJson[music_name.c_str()]["Score"]["Ez"].GetInt());
		gamescore->setString(Temporary);
		sprintf(Temporary, "Lv.%d", RecJson[music_name.c_str()]["Diff"]["Ez"].GetInt());
		gamediff->setString(Temporary);
		sprintf(Temporary, "%s", RecJson[music_name.c_str()]["Level"]["Ez"].GetString());
		gameLevel->setString(Temporary);
	}
	else if (Pick_diff == 2)
	{
		sprintf(Temporary, "%08d", RecJson[music_name.c_str()]["Score"]["Hd"].GetInt());
		gamescore->setString(Temporary);
		sprintf(Temporary, "Lv.%d", RecJson[music_name.c_str()]["Diff"]["Hd"].GetInt());
		gamediff->setString(Temporary);
		sprintf(Temporary, "%s", RecJson[music_name.c_str()]["Level"]["Hd"].GetString());
		gameLevel->setString(Temporary);
	}
	else if (Pick_diff == 3)
	{
		sprintf(Temporary, "%08d", RecJson[music_name.c_str()]["Score"]["In"].GetInt());
		gamescore->setString(Temporary);
		sprintf(Temporary, "Lv.%d", RecJson[music_name.c_str()]["Diff"]["In"].GetInt());
		gamediff->setString(Temporary);
		sprintf(Temporary, "%s", RecJson[music_name.c_str()]["Level"]["In"].GetString());
		gameLevel->setString(Temporary);
	}

	//更新速度
	Rec = FileUtils::getInstance()->getStringFromFile("Record/GameSet.json");
	RecJson.Parse<rapidjson::kParseDefaultFlags>(Rec.c_str());
	Play_Sp = RecJson["Speed"].GetFloat();
	auto gamespeed = (Label*)this->getChildByTag(9);
	sprintf(Temporary, "%.1f", Play_Sp);
	gamespeed->setString(Temporary);

	if (PLay_Back == 2)
	{
		PLay_Back = 0;
		gameplay(this);
	}

}

void MenuPick_2::backmeun()
{
	Director::getInstance()->popScene();
}

char* MenuPick_2::FontToUTF8(const char* font)
{
	int len = MultiByteToWideChar(CP_ACP, 0, font, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, font, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr)delete[] wstr;
	return str;
}

void MenuPick_2::gameplay(Ref* pSender)
{
	Filename = music_name;
	if (Pick_diff == 1)
	{
		Diff = "Ez";
	}
	else if (Pick_diff == 2)
	{
		Diff = "Hd";
	}
	else if (Pick_diff == 3)
	{
		Diff = "In";
	}
	Scene* scene = GamePlay::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(1.5, scene));
}

void MenuPick_2::restartplay(Ref* pSender)
{
	PLay_Back = 0;
	Filename = music_name;
	if (Pick_diff == 1)
	{
		Diff = "Ez";
	}
	else if (Pick_diff == 2)
	{
		Diff = "Hd";
	}
	else if (Pick_diff == 3)
	{
		Diff = "In";
	}
	Scene* scene = GamePlay::createScene();
	Director::getInstance()->pushScene(scene);
}