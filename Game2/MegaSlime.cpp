#include "stdafx.h"
#include "MegaSlime.h"

MegaSlime::MegaSlime()
{
	this->collider = new ObRect();
	this->skin_run = new ObImage(L"MegaSlimeBlue.png");

	status = MONSTER_STATUS::NORMAL;
	action = MONSTER_ACTION::IDLE;
	dir = MONSTER_DIRECTION::D;
	type = MONSTER_TYPE::MINION;

	hp = 25;
	speed = 50;
	exp = 5;
	damage = 5;
	defence = 0;
}

MegaSlime::~MegaSlime()
{
	delete collider;
	delete skin_run;

	TEXTURE->DeleteTexture(L"MegaSlimeBlue.png");
}

void MegaSlime::Init()
{
	this->collider->SetWorldPos(Vector2(RANDOM->Int(-1000, 1000), RANDOM->Int(-1000, 1000)));
	this->collider->isFilled = false;
	this->collider->scale = Vector2(40, 40);

	this->skin_run->SetParentRT(*this->collider);
	this->skin_run->maxFrame.x = 6;
	this->skin_run->maxFrame.y = 4;
	this->skin_run->scale.x = skin_run->imageSize.x / skin_run->maxFrame.x * 4;
	this->skin_run->scale.y = skin_run->imageSize.y / skin_run->maxFrame.y * 4;
	this->skin_run->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
}

void MegaSlime::Update()
{
	// 점프모션에만 이동
	if (skin_run->frame.x > 1) Monster::Update();
	else 
	{
		collider->Update();
		skin_run->Update();
	}

	switch (this->dir)
	{
	case MONSTER_DIRECTION::U: this->skin_run->frame.y = 0; break;
	case MONSTER_DIRECTION::L: this->skin_run->frame.y = 1; break;
	case MONSTER_DIRECTION::R: this->skin_run->frame.y = 2; break;
	case MONSTER_DIRECTION::D: this->skin_run->frame.y = 3; break;
	default: break;
	}
}

void MegaSlime::Render()
{
	if (GM->DEBUG_MODE)
		this->collider->Render();
	this->skin_run->Render();
}