#include "Note_Tap.h"
#include "GamePlay.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>
using namespace CocosDenshion;

extern int Note_strack[4];//4�����
extern bool Play_TimeStop;

Note::Note(int x, int y, float speed)
{
	Note_x = x;//Track���
	Note_y = y;//��������
	Note_speed = speed;//�ٶ�
}

void Note::Note_down()
{

	//auto moveTo = MoveTo::create(2.0f, Vec3(250, 0, 1));
	//Sequence������˳��ִ�У�CallFunc�ص��������ƶ�������ɺ����
	//this->runAction(Sequence::create(moveTo, CallFunc::create(CC_CALLBACK_0(Note::Note_end, this)), NULL));
	//����һ����ʱ��������״̬
	this->schedule(CC_SCHEDULE_SELECTOR(Note::Note_update));

}

void Note::Note_end()
{

	this->removeFromParentAndCleanup(true);
	//����remove��parent���룬����clear�Լ�
	//���ֱ��delete�Ļ����ᱨ��Ҫɾ���Ķ���ǰ������������״̬
	delete this;

}

void Note::Note_update(float dt)
{	
	if (Play_TimeStop)return;

	int X = Note_x;
	int Speed = Note_speed;
	this->setPosition(this->getPosition() + Vec2(0, -Note_speed));
	
	//PERFECT
	//�ж�����80+-ms��9.6֡
	if (this->getPositionY() <= (165 + 9.6 * Speed) && this->getPositionY() >= (165 - 9.6 * Speed))
	{
		if ((Note_strack[0] == 1 && Note_x == 1)|| (Note_strack[1] == 1 && Note_x == 2) || 
			(Note_strack[2] == 1 && Note_x == 3) || (Note_strack[3] == 1 && Note_x == 4))
		{
			//������Ч
			SimpleAudioEngine::getInstance()->playEffect("Music file/Tap_Perfect.mp3");
			//������Ч
			auto Note_layer = (LayerColor*)this->getParent();
			auto Icon = Sprite::create("Note icon/Note_Great.png");
			Icon->setPosition(Vec2(Director::getInstance()->
				getVisibleSize().width / 2 - 380 + X * 152, 148));
			Icon->setOpacity(0);
			Note_layer->addChild(Icon, 2);
			auto fade_1 = FadeTo::create(0.3f, 200);
			auto rota = RotateTo::create(0.3f, 90);
			auto spawn = Spawn::create(fade_1, rota, NULL);
			auto keep = FadeTo::create(0.5f, 200);
			auto fade_2 = FadeTo::create(0.8f, 0);
			//Sequence������˳��ִ�У�CallFunc�ص��������ƶ�������ɺ����
			Icon->runAction(Sequence::create(spawn, keep, fade_2, CallFunc::create(CC_CALLBACK_0(
				Sprite::removeFromParent, Icon)), NULL));
			//������Ч
			auto Particle = ParticleSystemQuad::create("Particle/Note_Perfect.plist");
			Particle->setPosition(Point(Director::getInstance()->
				getVisibleSize().width / 2 - 380 + X * 152, this->getPositionY() - 8));
			Note_layer->addChild(Particle, 1);
			//�ӷ֣��ҵ����ڵ�ĸ��ڵ㣬Ҳ����GamePlay
			auto PlayFather = ((GamePlay*)(LayerColor*)this->getParent()->getParent());
			PlayFather->Play_Perfect++;
			PlayFather->Play_Combo++;
			PlayFather->Play_Score = PlayFather->Play_Score + PlayFather->Play_GetScore;
			this->removeFromParentAndCleanup(true);
			delete this;
		}
	}
	//GRAET
	//�ж�����200+-ms��24֡
	else if (this->getPositionY() <= (165 + 24 * Speed) && this->getPositionY() >= (165 - 24 * Speed))
	{
		if ((Note_strack[0] == 1 && Note_x == 1) || (Note_strack[1] == 1 && Note_x == 2) ||
			(Note_strack[2] == 1 && Note_x == 3) || (Note_strack[3] == 1 && Note_x == 4))
		{
			SimpleAudioEngine::getInstance()->playEffect("Music file/Tap_Good.mp3");

			auto Note_layer = (LayerColor*)this->getParent();
			auto Icon = Sprite::create("Note icon/Note_Good.png");
			Icon->setPosition(Vec2(Director::getInstance()->
				getVisibleSize().width / 2 - 380 + X * 152, 148));
			Icon->setOpacity(0);
			Note_layer->addChild(Icon, 2);
			auto fade_1 = FadeTo::create(0.3f, 200);
			auto rota = RotateTo::create(0.3f, 90);
			auto spawn = Spawn::create(fade_1, rota, NULL);
			auto keep = FadeTo::create(0.5f, 200);
			auto fade_2 = FadeTo::create(0.8f, 0);
			Icon->runAction(Sequence::create(spawn, keep, fade_2, CallFunc::create(CC_CALLBACK_0(
				Sprite::removeFromParent, Icon)), NULL));

			auto Particle = ParticleSystemQuad::create("Particle/Note_Good.plist");
			Particle->setPosition(Point(Director::getInstance()->
				getVisibleSize().width / 2 - 380 + X * 152, this->getPositionY() - 8));
			Note_layer->addChild(Particle, 1);
			auto PlayFather = ((GamePlay*)(LayerColor*)this->getParent()->getParent());
			PlayFather->Play_Good++;
			PlayFather->Play_Combo++;
			PlayFather->Play_Score = PlayFather->Play_Score + PlayFather->Play_GetScore*0.65;
			this->removeFromParentAndCleanup(true);
			delete this;
		}
	}
	//BAD
	else if (this->getPositionY() < (165 - 24 * Speed))
	{
		((GamePlay*)(LayerColor*)this->getParent()->getParent())->Play_Pass++;
		((GamePlay*)(LayerColor*)this->getParent()->getParent())->Play_Combo = 0;
		this->removeFromParentAndCleanup(true);
		//����remove��parent���룬����clear�Լ�
		//���ֱ��delete�Ļ����ᱨ��Ҫɾ���Ķ���ǰ������������״̬
		delete this;
	}		
	//�ڰ��°���������
	if (Note_strack[X - 1] == 1)
	{
		Note_strack[X - 1] = -1;
	}

}