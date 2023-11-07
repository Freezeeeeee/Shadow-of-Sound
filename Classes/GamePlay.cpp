#include "GamePlay.h"
#include "GamePause.h"
#include "Note_Tap.h"
#include "Note_Hold.h"
#include "winuser.h"

#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>
using namespace CocosDenshion;
using namespace rapidjson;

USING_NS_CC;

int Note_strack[4] = { 0 };//���
float Play_Sp;//�ٶȵ���
extern std::string Diff;//�Ѷ����
extern std::string Filename;//�ļ���
bool Play_TimeStop = false;//ʱͣ
bool Play_TimeResume = false;//ʱ��
int PLay_Back = 0;//�жϷ���/�ؿ�

Scene* GamePlay::createScene()
{
	return GamePlay::create();
}

bool GamePlay::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Background��,tag0,���µ�Line,tag0,BackLine,tag1
	auto Backlayer = LayerColor::create(Color4B::WHITE);
	std::string filename = "Cover/" + Filename + ".png";
	auto SkyStriker = Sprite::create(filename);
	SkyStriker->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	SkyStriker->setOpacity(255);
	Backlayer->addChild(SkyStriker, 0);
	//Line
	auto Line = DrawNode::create();
	Line->drawSolidRect(Vec2(visibleSize.width/2-303, 150), Vec2
	(visibleSize.width / 2 + 303, 146), Color4F::WHITE);
	Backlayer->addChild(Line, 1, 0);
	this->addChild(Backlayer, 1, 0);
	//����
	auto BackLine = Sprite::create("Note icon/BackLine2.png");
	BackLine->setAnchorPoint(Vec2(0, 1));
	BackLine->setPosition(Vec2(0, visibleSize.height));
	BackLine->setOpacity(200);
	Backlayer->addChild(BackLine, 0, 1);

	//Note������
	auto Notelayer = LayerColor::create();
	this->addChild(Notelayer, 1, 5);
	//�ƹ�
	auto LightingL1 = Sprite::create("Note icon/Left_1.png");
	LightingL1->setAnchorPoint(Vec2(0, 0));
	LightingL1->setPosition(Vec2(visibleSize.width / 2-303, 0));
	LightingL1->setOpacity(0);
	Notelayer->addChild(LightingL1, 2);
	auto LightingL2 = Sprite::create("Note icon/Left_2.png");
	LightingL2->setAnchorPoint(Vec2(0, 0));
	LightingL2->setPosition(Vec2(visibleSize.width / 2 - 151, 0));
	LightingL2->setOpacity(0);
	Notelayer->addChild(LightingL2, 2);
	auto LightingR1 = Sprite::create("Note icon/Right_1.png");
	LightingR1->setAnchorPoint(Vec2(0, 0));
	LightingR1->setPosition(Vec2(visibleSize.width / 2 + 153, 0));
	LightingR1->setOpacity(0);
	Notelayer->addChild(LightingR1, 2);
	auto LightingR2 = Sprite::create("Note icon/Right_2.png");
	LightingR2->setAnchorPoint(Vec2(0, 0));
	LightingR2->setPosition(Vec2(visibleSize.width / 2 + 1, 0));
	LightingR2->setOpacity(0);
	Notelayer->addChild(LightingR2, 2);

	//������ʾ����
	auto BackKey = Sprite::create("Note icon/Key.png");
	BackKey->setAnchorPoint(Vec2(0.5, 0));
	BackKey->setPosition(Vec2(visibleSize.width / 2, 0));
	BackKey->setOpacity(0);
	Notelayer->addChild(BackKey, 2);
	auto Delay_1 = DelayTime::create(1.0f);
	auto Fade_1 = FadeTo::create(1.0f, 0);
	auto Delay_2 = DelayTime::create(3.0f);
	auto Fade_2 = FadeTo::create(1.0f, 255);
	auto Disappear = Sequence::create(Delay_1, Fade_2, Delay_2, Fade_1, NULL);
	BackKey->runAction(Disappear);

	//Combo����
	auto Combo = Label::createWithTTF("COMBO", "fonts/arial.ttf", 48);
	Combo->setTextColor(Color4B(139,215,250,255));
	auto Number_Combo = Label::createWithTTF(" ", "fonts/arial.ttf", 48);
	Number_Combo->setTextColor(Color4B(139, 215, 250, 255));
	//Notelayer,tag5,����Combo,tag0,Number_Combo,tag1,����Score,tag2,���㻭��,tag3
	Notelayer->addChild(Combo, 3, 0);
	Notelayer->addChild(Number_Combo, 3, 1);
	Combo->setPosition(Vec2(visibleSize.width / 2, 1020));
	Number_Combo->setPosition(Vec2(visibleSize.width / 2, 965));
	
	//�Ʒ�
	auto ScoreLable = Label::createWithTTF(" ", "fonts/Saira-Regular.ttf", 30);
	ScoreLable->setTextColor(Color4B::WHITE);
	Notelayer->addChild(ScoreLable, 3, 2);
	ScoreLable->setAnchorPoint(Vec2(1, 1));
	ScoreLable->setPosition(Vec2(visibleSize.width/2+300, visibleSize.height));

	/*����һ����ʱ��,tag1
	auto Timelabel = Label::createWithTTF("Time:0", "fonts/Marker Felt.ttf", 24);
	Timelabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	Timelabel->setTextColor(Color4B::WHITE);
	this->addChild(Timelabel, 1, 1);*/

	this->schedule(CC_SCHEDULE_SELECTOR(GamePlay::Update_count));

	//�ٶ�,Ez4,Hd6,In8
	if (Diff == "Ez")
		Play_speed = 4;
	else if(Diff == "Hd")
		Play_speed = 6;
	else
		Play_speed = 8;

	/*����������
	auto MusicFile = FileUtils::getInstance();
	auto Musicscore = MusicFile->getStringFromFile("Music score/Escaping Gravity -TheFatRat.txt");
	auto Timelabel1 = Label::createWithTTF(Musicscore, "fonts/Marker Felt.ttf", 24);
	Timelabel1->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 4));
	Timelabel1->setTextColor(Color4B::BLACK);
	this->addChild(Timelabel1, 1, 2);*/

	//��������
	GamePre();

	/*ͼ�����
	auto Azelia = Sprite::create("Note icon/Note_tap.png");
	Azelia->setAnchorPoint(Vec2(0, 1));
	Azelia->setPosition(Vec2(visibleSize.width / 2, 105));
	this->addChild(Azelia, 1);*/

	// creating a keyboard event listener
	auto listener = EventListenerKeyboard::create();
	//lambda�����ĺ�������
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		/*��ΪEventKeyboard::KeyCode::KEYÿֻ֡�ܼ��һ�������������ζ԰���ʱ����Ҫ��ϸ�
		���磬˫Ѻ��ͬʱ����
		���Ծ���GetAsyncKeyState()��Ϊ����ʱ����*/
		/*����
		if(keyCode == EventKeyboard::KeyCode::KEY_W)
		{
			SimpleAudioEngine::getInstance()->playEffect("Music file/Tap_Good.mp3");
			auto note = new Note(1, 1, 1);
			note->initWithFile("Note icon/Note_tap.png");
			note->setAnchorPoint(Vec2(0, 1));
			note->setPosition(visibleSize.width/2 - 303, 1000);
			auto Note_layer = (LayerColor*)this->getChildByTag(5);
			Note_layer->addChild(note, 1);
			note->Note_down();
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_E)
		{
			SimpleAudioEngine::getInstance()->playEffect("Music file/Tap_Good.mp3");
			auto note = new Note(2, 1, 2);
			note->initWithFile("Note icon/Note_tap.png");
			note->setAnchorPoint(Vec2(0, 1));
			note->setPosition(visibleSize.width / 2 - 151, 1000);
			auto Note_layer = (LayerColor*)this->getChildByTag(5);
			Note_layer->addChild(note, 1);
			note->Note_down();
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_U)
		{
			SimpleAudioEngine::getInstance()->playEffect("Music file/Tap_Perfect.mp3");
			auto note = new Note(3, 1, 4);
			note->initWithFile("Note icon/Note_tap.png");
			note->setAnchorPoint(Vec2(0, 1));
			note->setPosition(visibleSize.width / 2 + 1, 1000);
			auto Note_layer = (LayerColor*)this->getChildByTag(5);
			Note_layer->addChild(note, 1);
			note->Note_down();
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_I)
		{
			SimpleAudioEngine::getInstance()->playEffect("Music file/Tap_Perfect.mp3");
			auto note = new Note(4, 1, 8);
			note->initWithFile("Note icon/Note_tap.png");
			note->setAnchorPoint(Vec2(0, 1));
			note->setPosition(visibleSize.width / 2 + 153, 1000);
			auto Note_layer = (LayerColor*)this->getChildByTag(5);
			Note_layer->addChild(note, 1);
			note->Note_down();
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_R)
		{
			auto note = new Hold(1, 500, 1);
			note->Hold_length = note->Hold_y;
			note->initWithFile("Note icon/Note_hold.png");
			note->setCapInsets(Rect(3, 3, 143, 143));
			//��������λ�ã���������
			note->setAnchorPoint(Vec2(0, 1));
			note->setPosition(visibleSize.width / 2 - 303, 1000);
			note->setContentSize(Size(150, note->Hold_y));
			auto Note_layer = (LayerColor*)this->getChildByTag(5);
			Note_layer->addChild(note, 1);
			note->Hold_down();
		}*/
		if (GetAsyncKeyState('A') & 0x8000 && Note_strack[0] != -1)
		{
			Note_strack[0] = 1;
			//�ƹ�����
			LightingL1->setOpacity(255);
		}
		if (GetAsyncKeyState('S') & 0x8000 && Note_strack[1] != -1)
		{
			Note_strack[1] = 1;
			LightingL2->setOpacity(255);
		}
		if (GetAsyncKeyState(VK_OEM_1) & 0x8000 && Note_strack[2] != -1)
		{
			Note_strack[2] = 1;
			LightingR2->setOpacity(255);
		}
		if (GetAsyncKeyState(VK_OEM_7) & 0x8000 && Note_strack[3] != -1)
		{
			Note_strack[3] = 1;
			LightingR1->setOpacity(255);
		}
		/*��������
		else if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			char table[32];
			auto Timelabel2 = (Label*)this->getChildByTag(2);
			if (!Game_file.empty())
			{
				sprintf(table, "Musicscore:%f", Game_file.front());
				Game_file.pop_front();
			}
			Timelabel2->setString(table);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE && !Play_End)
		{
			GameEnd();
		}*/
	};
	//�ɿ�����ʱ
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE && !Play_End && !Play_TimeStop)
		{
			Play_TimeStop = true;
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			GamePause(this);
		}
			
		if (keyCode == EventKeyboard::KeyCode::KEY_ENTER && Play_End) 
		{
			backmeun(this);
		}
		
		//�ָ���������,û��ô�ϸ��ֱ����EventKeyboard::KeyCode��
		else if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			Note_strack[0] = 0;
			//�ƹ�Ϩ��
			LightingL1->setOpacity(0);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_S)
		{
			Note_strack[1] = 0;
			LightingL2->setOpacity(0);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_SEMICOLON)
		{
			Note_strack[2] = 0;
			LightingR2->setOpacity(0);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_APOSTROPHE)
		{
			Note_strack[3] = 0;
			LightingR1->setOpacity(0);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//��ȡJson�ļ�
	std::string Rec = FileUtils::getInstance()->getStringFromFile("Record/GameRecord.json");
	RecJson.Parse<rapidjson::kParseDefaultFlags>(Rec.c_str());

	return true;
}

void GamePlay::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void GamePlay::Update_count(float dt)
{
	if (PLay_Back != 0)
	{
		GamePlay::backmeun(this);
	}
	else if (Play_TimeResume)
	{
		Play_TimeResume = false;
		Play_TimeStop = false;
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
	else if (Play_TimeStop)return;//ʱͣ

	//���㲥������
	else if (Game_time == (int)((Director::getInstance()->getVisibleSize().height - 165)
		/ (Play_speed*Play_Sp)))
	{
		std::string filename = "Music library/" + Filename + ".mp3";
		SimpleAudioEngine::getInstance()->playBackgroundMusic(filename.data());
		Play_Start = true;
	}
	//������
	else if ((!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) 
		&& Play_Start)
	{
		Play_Start = false;
		Play_End = true;
		GameEnd();
	}
		
	Game_time++;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	/*����
	//��ȡ tag=1 ��Label
	char time[32];
	auto Timelabel = (Label*)this->getChildByTag(1);
	sprintf(time, "Time:%08d", (int)Game_time/120);
	Timelabel->setString(time);*/

	//����һ��Comboֵ
	char combo[32];
	auto ComboNumer = (Label*)(Layer*)this->getChildByTag(5)->getChildByTag(1);
	sprintf(combo, "%d", Play_Combo);
	ComboNumer->setString(combo);
	if (Play_MaxCombo < Play_Combo)
		Play_MaxCombo = Play_Combo;
	static int Cb_one = 0;
	static int Cb_two = 0;
	//��combo������Ч
	if (Play_Combo % 100 == 0 && Play_Combo!=0)
	{
		if (Cb_one == Cb_two)
		{
			Game_combo();
			Cb_one++;
		}
	}
	else if (Cb_one != Cb_two)
	{
		Cb_two++;
	}

	//���·���
	char score[32];
	auto ScoreNumer = (Label*)(Layer*)this->getChildByTag(5)->getChildByTag(2);
	sprintf(score, "%07d", Play_Score);
	ScoreNumer->setString(score);

	//��������
	if (Game_file.empty())
		;
	else if ((int)(Game_file.front()*120) == Game_time)//����ʱ��
	{
		CreateNote(Game_time);
	}
}

void GamePlay::Game_combo()
{

	auto Particle_1 = ParticleSystemQuad::create("Particle/Combo_100.plist");
	Particle_1->setPosition(Point(Director::getInstance()->
		getVisibleSize().width / 2 - 580, this->getPositionY()));
	auto Particle_2 = ParticleSystemQuad::create("Particle/Combo_100.plist");
	Particle_2->setPosition(Point(Director::getInstance()->
		getVisibleSize().width / 2 + 580, this->getPositionY()));
	auto Note_layer = (LayerColor*)this->getChildByTag(0);
	Note_layer->addChild(Particle_1, 1);
	Note_layer->addChild(Particle_2, 1);
}

void GamePlay::CreateNote(int time)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Game_file.pop_front();
	int X = Game_file.front();//���ɹ��
	Game_file.pop_front();
	float Speed = Game_file.front()*Play_Sp;//�ٶ�
	Game_file.pop_front();
	int Y = (int)Game_file.front();//����
	Game_file.pop_front();
	if (Y == 1)//Tap
	{
		auto note = new Note(X, Y, Speed);
		//��ʵ�ϣ������Ǵ�������ʱ��cocos2dx�Ѿ������������˻���
		note->initWithFile("Note icon/Note_tap.png");
		//ê������������λ��
		note->setAnchorPoint(Vec2(0, 1));
		note->setPosition(visibleSize.width / 2 - 455 + X * 152, visibleSize.height+15);
		//������Note��
		auto Note_layer = (LayerColor*)this->getChildByTag(5);
		Note_layer->addChild(note, 1);
		note->Note_down();
	}
	else//Hold
	{
		auto note = new Hold(X, Y* Speed, Speed);
		note->initWithFile("Note icon/Note_hold.png");
		note->setCapInsets(Rect(3, 3, 143, 143));
		note->setAnchorPoint(Vec2(0, 1));
		note->setPosition(visibleSize.width / 2 - 455 + X * 152, visibleSize.height+Y * Speed);
		note->setContentSize(Size(150, note->Hold_y));
		auto Note_layer = (LayerColor*)this->getChildByTag(5);
		Note_layer->addChild(note, 1);
		note->Hold_down();
	}
	
	
	
	//�ݹ飬�ж��Ƿ���ͬһʱ�����ɵ�����
	if (!Game_file.empty())
	{
		if ((int)(Game_file.front() * 120) == time)
		{
			CreateNote(time);
		}
	}
}


void GamePlay::GamePre()
{
	std::string filename = "Music library/" + Filename + ".mp3";
	//Ԥ���ظ���
	SimpleAudioEngine::getInstance()->preloadEffect(filename.data());
	//��ȡ�����ļ�
	auto MusicFile = FileUtils::getInstance();
	filename = "Music score/"+ Diff+"_" + Filename + ".txt";
	auto Musicscore = MusicFile->getStringFromFile(filename);
	//�ַ���ת��Ϊfloat���ӽ�list
	char Temporary[12] = { 0 };
	int i, tk;
	float tpr = 0;
	for (i = 0, tk = 0; i <= (int)Musicscore.length()-1; i++) {

		if (Musicscore[i] != '\n' && Musicscore[i] != ' ' && Musicscore[i] != NULL)
		{
			Temporary[tk] = Musicscore[i];
			tk++;
		}
		else
		{
			tk = 0;
			sscanf(Temporary, "%f", &tpr);
			Game_file.push_back(tpr);
			//��������
			Play_Toatal++;
			memset(Temporary, 0, sizeof(Temporary));
		}
	}
	Play_Toatal = Play_Toatal / 4;
	Play_GetScore = 1000000 / Play_Toatal;
	/*������
	char table[32];
	auto Timelabel2 = (Label*)this->getChildByTag(2);
	Timelabel2->setString(table);
	sprintf(table, "Musicscore:%f", tpr);*/
}

void GamePlay::GameEnd()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto Back_layer = (LayerColor*)this->getChildByTag(0);
	auto Note_layer = (LayerColor*)this->getChildByTag(5);
	auto fade_1 = FadeTo::create(1.0f, 0);
	auto delay = DelayTime::create(0.8f);
	auto fade_2 = FadeTo::create(0.5f, 255);
	auto disappear = Sequence::create(delay, fade_2, NULL);
	(DrawNode*)Back_layer->getChildByTag(0)->runAction(fade_1);
	(Sprite*)Back_layer->getChildByTag(1)->runAction(fade_1->clone());
	(Label*)Note_layer->getChildByTag(0)->runAction(fade_1->clone());
	(Label*)Note_layer->getChildByTag(1)->runAction(fade_1->clone());
	(Label*)Note_layer->getChildByTag(2)->runAction(fade_1->clone());
	auto GameEnd = Sprite::create("Cover/GameEnd.png");
	GameEnd->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	GameEnd->setOpacity(0);
	Note_layer->addChild(GameEnd, 3,3);
	GameEnd->runAction(disappear);

	char Temporary[32];
	sprintf(Temporary, "%08d", Play_Score);
	auto GameScore = Label::createWithTTF(Temporary, "fonts/Saira-Thin.ttf", 108);
	GameEnd->addChild(GameScore, 1);
	GameScore->setPosition(Vec2(1130, 650));
	sprintf(Temporary, "%d", Play_MaxCombo);
	auto GameMaxCombo = Label::createWithTTF(Temporary, "fonts/Saira-Thin.ttf", 96);
	//��Ϊ����ݻᵼ������ģ�������Բ��ò�˫����СȻ����С
	GameMaxCombo->setScale(0.5);
	GameEnd->addChild(GameMaxCombo, 1);
	GameMaxCombo->setPosition(Vec2(836, 275));
	sprintf(Temporary, "%d", Play_Perfect);
	auto GamePerfect = Label::createWithTTF(Temporary, "fonts/Saira-Thin.ttf", 72);
	GamePerfect->setScale(0.5);
	GameEnd->addChild(GamePerfect, 1);
	GamePerfect->setPosition(Vec2(1400, 425));
	sprintf(Temporary, "%d", Play_Good);
	auto GameGood = Label::createWithTTF(Temporary, "fonts/Saira-Thin.ttf", 72);
	GameGood->setScale(0.5);
	GameEnd->addChild(GameGood, 1);
	GameGood->setPosition(Vec2(1400, 367));
	sprintf(Temporary, "%d", Play_Bad);
	auto GameBad = Label::createWithTTF(Temporary, "fonts/Saira-Thin.ttf", 72);
	GameBad->setScale(0.5);
	GameEnd->addChild(GameBad, 1);
	GameBad->setPosition(Vec2(1400, 309));
	sprintf(Temporary, "%d", Play_Pass);
	auto GamePass = Label::createWithTTF(Temporary, "fonts/Saira-Thin.ttf", 72);
	GamePass->setScale(0.5);
	GameEnd->addChild(GamePass, 1);
	GamePass->setPosition(Vec2(1400, 251));

	auto GameName = Label::createWithTTF(Filename, "fonts/arial.ttf", 42);
	GameEnd->addChild(GameName, 1);
	GameName->setPosition(Vec2(710, 405));
	sprintf(Temporary, " Lv.%d", RecJson["Escaping Gravity -TheFatRat"]["Diff"][Diff.c_str()].GetInt());
	auto GameDiff = Label::createWithTTF(Diff + Temporary, "fonts/arial.ttf", 42);
	GameDiff->setAnchorPoint(Vec2(1, 0.5));
	GameEnd->addChild(GameDiff, 1);
	GameDiff->setPosition(Vec2(955, 345));

	//�������������
	auto GameLevel = Label::createWithTTF(" ", "fonts/Saira-Regular.ttf", 264);
	std::string Play_level;
	if (Play_Toatal == Play_Perfect)
	{
		Play_level = "Ap";
		GameLevel->setTextColor(Color4B::YELLOW);
	}
	else if (Play_Bad == 0 && Play_Pass == 0)
	{
		Play_level = "Fc";
		GameLevel->setTextColor(Color4B(0,255,255,255));
	}
	else if (Play_Score > 950000)
	{
		Play_level = "S";
	}
	else if (Play_Score > 900000)
	{
		Play_level = "A";
	}
	else if (Play_Score > 820000)
	{
		Play_level = "B";
	}
	else if (Play_Score > 650000)
	{
		Play_level = "C";
	}
	else
	{
		Play_level = "F";
	}
	GameLevel->setString(Play_level);
	GameEnd->addChild(GameLevel, 1);
	GameLevel->setPosition(Vec2(620, 680));

	//���㵽�ļ�
	if (RecJson[Filename.c_str()]["Score"][Diff.c_str()].GetInt() < Play_Score)
	{
		RecJson[Filename.c_str()]["Score"][Diff.c_str()].SetInt(Play_Score);
		RecJson[Filename.c_str()]["Level"][Diff.c_str()].SetString(Play_level.c_str(), Play_level.length());
	}
	//��json��������д���ļ���
	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	RecJson.Accept(writer);
	//FILE* Readfile = fopen("Resources/Record/GameRecord.json", "wb");
	//��֪��Ϊʲô����cocos2d-x����ֱ�������·��
	// ���ǲ��У����·������ʧ����
	// ��vs��ֱ�Ӵ�exe������steam�������Ǹ�����ͬ�����·����ȡ
	std::string filepath = FileUtils::getInstance()->fullPathForFilename("Record/GameRecord.json");
	FILE* Readfile = fopen(filepath.c_str(), "wb");
	fputs(buffer.GetString(), Readfile);
	fclose(Readfile);
}

void GamePlay::GamePause(Ref* pSender)
{
	auto TemperarySprite = Sprite::create();
	this->addChild(TemperarySprite);
	TemperarySprite->runAction(Sequence::create(DelayTime::create(1.0f),
		CallFunc::create(CC_CALLBACK_0(GamePlay::PauseAfter, this)), NULL));

	/*��Ϊnew������Ե�ʣ��ᵼ�£�
		�� �� й ¶

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
	
	this->pause();
	renderTexture->begin();            //��ʼץ��
	this->visit(); //������ǰ����Scene��ȫ���ӽڵ���Ϣ������renderTexture��
	renderTexture->end();				//����ץ��

	Scene* scene = GamePause::createScene(renderTexture);

	//���淽���в�ͨ��ֱ�ӽذ�
	//utils::captureScreen(CC_CALLBACK_2(GamePlay::PauseAfter, this), "PauseScreenShot.png");

	�⼸��������Ban��
	*/
}

void GamePlay::PauseAfter()
{
	//ǰ��֮������غ����ڴ�й©
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);

	this->pause();
	renderTexture->begin();            //��ʼץ��
	this->visit(); //������ǰ����Scene��ȫ���ӽڵ���Ϣ������renderTexture��
	renderTexture->end();				//����ץ��

	Scene* scene = GamePause::createScene(renderTexture);
	Director::getInstance()->pushScene(TransitionCrossFade::create(0.5, scene));
}

void GamePlay::backmeun(Ref* pSender)
{
	if(PLay_Back == 1)PLay_Back = 0;
	Play_TimeStop = false;
	Play_TimeResume = false;
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	Director::getInstance()->popScene();
}