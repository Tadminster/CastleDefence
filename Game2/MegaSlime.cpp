#include "stdafx.h"
#include "MegaSlime.h"

MegaSlime::MegaSlime()
{
	this->collider = new ObRect();
	this->skin_run = new ObImage(L"MegaSlimeBlue.png");
	this->skin_run->SetParentRT(*this->collider);

	hp = 25;
	speed = 50;
	exp = 5;
	damage = 5;
}

MegaSlime::~MegaSlime()
{
	delete collider;
	delete skin_run;

	TEXTURE->DeleteTexture(L"MegaSlime.png");
}

void MegaSlime::Init()
{
	this->collider->SetWorldPos(Vector2(RANDOM->Int(-1000, 1000), RANDOM->Int(-1000, 1000)));
	this->collider->isFilled = false;
	this->collider->scale = Vector2(40, 40);


	this->skin_run->scale = Vector2(80, 80);
	this->skin_run->maxFrame.x = 6;
	this->skin_run->maxFrame.y = 4;
}

void MegaSlime::Update()
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

void MegaSlime::Render()
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