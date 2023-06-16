#include "stdafx.h"
#include "KingMegaSlime.h"

KingMegaSlime::KingMegaSlime()
{
	this->collider = new ObRect();
	this->skin_run = new ObImage(L"KingSlimeBlue.png");
	this->skin_run->SetParentRT(*this->collider);

	hp = 75;
	speed = 60;
	exp = 15;
	damage = 10;
}

KingMegaSlime::~KingMegaSlime()
{
	delete collider;
	delete skin_run;

	TEXTURE->DeleteTexture(L"KingMegaSlime.png");
}

void KingMegaSlime::Init()
{
	this->collider->SetWorldPos(Vector2(RANDOM->Int(-1000, 1000), RANDOM->Int(-1000, 1000)));
	this->collider->isFilled = false;
	this->collider->scale = Vector2(55, 55);


	this->skin_run->scale = Vector2(90, 90);
	this->skin_run->maxFrame.x = 6;
	this->skin_run->maxFrame.y = 4;
}

void KingMegaSlime::Update()
{
	Monster::Update();

	if (this->dir == MonsterDir::L)
	{
		this->skin_run->frame.y = 1;
	}
	else if (this->dir == MonsterDir::R)
	{
		this->skin_run->frame.y = 2;
	}
	else if (this->dir == MonsterDir::U)
	{
		this->skin_run->frame.y = 0;
	}
	else if (this->dir == MonsterDir::D)
	{
		this->skin_run->frame.y = 3;
	}
}

void KingMegaSlime::Render()
{
	if (DEBUG_MODE)
		this->collider->Render();
	this->skin_run->Render();

	static float frameTick = 0.0f;
	if (TIMER->GetTick(frameTick, 0.4f))
	{
		skin_run->frame.x++;

		if (skin_run->frame.x % skin_run->maxFrame.x == 0)
			skin_run->frame.x = 1;
	}
	//Monster::Render();
}