#include "Note_Hold.h"
#include "GamePlay.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>
using namespace CocosDenshion;

extern int Note_strack[4];//4条轨道
extern bool Play_TimeStop;

Hold::Hold(int x, int y, float speed)
{
	Hold_x = x;//Track轨道
	Hold_y = y;//音符种类
	Hold_speed = speed;//速度
	Hold_length = Hold_y;
}

void Hold::Hold_down()
{
	auto itemBg = cocos2d::ui::Scale9Sprite::create("pop/achieve_itembg.png");
	this->schedule(CC_SCHEDULE_SELECTOR(Hold::Hold_update));
}

void Hold::Hold_end()
{

	this->removeFromParentAndCleanup(true);
	//调用remove与parent分离，并且clear自己
	//如果直接delete的话，会报错要删除的对象当前还是正在运行状态
	delete this;

}

void Hold::Hold_update(float dt)
{
	if (Play_TimeStop)return;

	int X = Hold_x;
	int Speed = Hold_speed;
	this->setPosition(this->getPosition() + Vec2(0, -Hold_speed));

	//Hold进入判定线后的缩放
	Vec2 orginal = this->getPosition();
	if (this->getPositionY() <= 150)
	{
		this->Hold_y = 0;
		this->setContentSize(Size(0, 0));
	}
	else if ((this->Hold_y > this->getPositionY() - 148) && this->Hold_y != 0)
	{
		this->Hold_y = this->getPositionY() - 148;
		this->setContentSize(Size(150, this->Hold_y));
	}

	//PERFECT
	if (this->getPositionY() - Hold_length <= 150 + 9.6 * Speed && this->getPositionY()
		- Hold_length >= 150 - 9.6 * Speed && Hold_state == 0)
	{
		if ((Note_strack[0] == 1 && Hold_x == 1) || (Note_strack[1] == 1 && Hold_x == 2) ||
			(Note_strack[2] == 1 && Hold_x == 3) || (Note_strack[3] == 1 && Hold_x == 4))
		{
			SimpleAudioEngine::getInstance()->playEffect("Music file/Note_One.mp3");
			Music_number = SimpleAudioEngine::getInstance()->playEffect("Music file/Note_Two.mp3");
			//动作特效
			auto Note_layer = (LayerColor*)this->getParent();
			Icon = Sprite::create("Note icon/Note_Great.png");
			Icon->setPosition(Vec2(Director::getInstance()->
				getVisibleSize().width / 2 - 380 + X * 152, 148));
			Icon->setOpacity(0);
			Note_layer->addChild(Icon, 2);
			auto fade_1 = FadeTo::create(0.3f, 200);
			auto rota = RotateTo::create(0.3f, 90);
			auto spawn = Spawn::create(fade_1, rota, NULL);
			Icon->runAction(spawn);

			Hold_state = 1;
			//this->setOpacity(200);
			Hold_PorG = 1;
		}
	}
	//GRAET
	else if (this->getPositionY() - Hold_length <= 150 + 24 * Speed && this->getPositionY()
		- Hold_length >= 150 - 24 * Speed && Hold_state == 0)
	{
		if ((Note_strack[0] == 1 && Hold_x == 1) || (Note_strack[1] == 1 && Hold_x == 2) ||
			(Note_strack[2] == 1 && Hold_x == 3) || (Note_strack[3] == 1 && Hold_x == 4))
		{
			SimpleAudioEngine::getInstance()->playEffect("Music file/Note_One.mp3");
			Music_number = SimpleAudioEngine::getInstance()->playEffect("Music file/Note_Two.mp3");

			auto Note_layer = (LayerColor*)this->getParent();
			Icon = Sprite::create("Note icon/Note_Good.png");
			Icon->setPosition(Vec2(Director::getInstance()->
				getVisibleSize().width / 2 - 380 + X * 152, 148));
			Icon->setOpacity(0);
			Note_layer->addChild(Icon, 2);
			auto fade_1 = FadeTo::create(0.3f, 200);
			auto rota = RotateTo::create(0.3f, 90);
			auto spawn = Spawn::create(fade_1, rota, NULL);
			Icon->runAction(spawn);

			Hold_state = 1;
			//this->setOpacity(200);
		}
	}

	//Hold粒子特效
	if ((Hold_state == 1 || Hold_state == 2) && getPositionY() > 150)
	{
		if (Cycle == 10)
		{
			auto Particle = ParticleSystemQuad::create("Particle/Hold_Perfect.plist");
			Particle->setPosition(Point(Director::getInstance()->
				getVisibleSize().width / 2 - 380 + X * 152, 148));
			auto Note_layer = (LayerColor*)this->getParent();
			Note_layer->addChild(Particle, 1);
			Cycle = 0;
		}
		else
			Cycle++;
	}
	//动作特效的结束
	if (Hold_state == 2 && getPositionY() < 150 && End == false)
	{
		auto icon = Icon;
		icon->cleanup();
		auto fade_1 = FadeTo::create(0.3f, 0);
		auto rota = RotateTo::create(0.3f, 180);
		auto spawn = Spawn::create(fade_1, rota, NULL);
		icon->runAction(Sequence::create(spawn, CallFunc::create(CC_CALLBACK_0(
			Sprite::removeFromParent, icon)), NULL));
		End = true;
	}

	//在按下按键后锁定
	if (Note_strack[X - 1] == 1 && (Hold_state == 0 || Hold_state == 1))
	{
		Note_strack[X - 1] = -1;
	}

	//放手之时
	//隐去
	if (this->getPositionY() - Hold_length < 150 - 24 * Speed && Hold_state == 0)
	{
		this->setOpacity(120);
		Hold_state = -1;
		((GamePlay*)(LayerColor*)this->getParent()->getParent())->Play_Pass++;
		((GamePlay*)(LayerColor*)this->getParent()->getParent())->Play_Combo = 0;
	}
	else if (Hold_state == 1 && Note_strack[X - 1] == 0)
	{
		auto icon = Icon;
		icon->cleanup();
		auto fade_1 = FadeTo::create(0.3f, 0);
		auto rota = RotateTo::create(0.3f, 180);
		auto spawn = Spawn::create(fade_1, rota, NULL);
		icon->runAction(Sequence::create(spawn, CallFunc::create(CC_CALLBACK_0(
			Sprite::removeFromParent, icon)), NULL));
		((GamePlay*)(LayerColor*)this->getParent()->getParent())->Play_Bad++;
		((GamePlay*)(LayerColor*)this->getParent()->getParent())->Play_Combo = 0;
		this->setOpacity(120);
		Hold_state = -1;
	}
	//成功
	else if (this->getPositionY() <= 150 + 24 * Speed && Hold_state == 1 && Note_strack[X - 1] == -1)
	{
		auto PlayFather = ((GamePlay*)(LayerColor*)this->getParent()->getParent());
		Hold_state = 2;
		if (Hold_PorG == 1)
		{
			PlayFather->Play_Perfect++;
			PlayFather->Play_Score = PlayFather->Play_Score + PlayFather->Play_GetScore;
		}
		else
		{
			PlayFather->Play_Good++;
			PlayFather->Play_Score = PlayFather->Play_Score + PlayFather->Play_GetScore*0.65;
		}
		PlayFather->Play_Combo++;
	}
	//End
	else if (this->getPositionY() < 150 - 24 * Speed)
	{
		this->removeFromParentAndCleanup(true);
		//调用remove与parent分离，并且clear自己
		//如果直接delete的话，会报错要删除的对象当前还是正在运行状态
		delete this;
	}
}