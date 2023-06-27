#include "stdafx.h"
#include "Slime.h"

Slime::Slime()
{
	this->collider = new ObRect();
	this->skin_run = new ObImage(L"Slime.png");

	hp = 15;
	speed = 40;
	exp = 1;
	damage = 5;
	defence = 0;
}

Slime::~Slime()
{
	delete collider;
	delete skin_run;

	TEXTURE->DeleteTexture(L"Slime.png");
}

void Slime::Init()
{
	this->collider->SetWorldPos(Vector2(RANDOM->Int(-1000, 1000), RANDOM->Int(-1000, 1000)));
	this->collider->isFilled = false;
	this->collider->scale = Vector2(35, 35);

	this->skin_run->SetParentRT(*this->collider);
	this->skin_run->scale = Vector2(60, 60);
	this->skin_run->maxFrame.x = 6;
	this->skin_run->maxFrame.y = 4;
	this->skin_run->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
}

void Slime::Update()
{
	// 점프모션에만 이동
	if (skin_run->frame.x > 1) Monster::Update();

	switch (this->dir)
	{
	case MonsterDir::U: this->skin_run->frame.y = 0; break;
	case MonsterDir::L: this->skin_run->frame.y = 1; break;
	case MonsterDir::R: this->skin_run->frame.y = 2; break;
	case MonsterDir::D: this->skin_run->frame.y = 3; break;
	default: break;
	}
}

void Slime::Render()
{
	if (GM->DEBUG_MODE)
		this->collider->Render();
	this->skin_run->Render();
}