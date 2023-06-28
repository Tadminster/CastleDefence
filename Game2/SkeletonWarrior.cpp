#include "stdafx.h"
#include "SkeletonWarrior.h"

SkeletonWarrior::SkeletonWarrior()
{
	this->collider = new ObRect();
	this->skin_run = new ObImage(L"SkeletonWarrior.png");

	status = MONSTER_STATUS::NORMAL;
	action = MONSTER_ACTION::RUN;
	dir = MONSTER_DIRECTION::D;
	type = MONSTER_TYPE::MINION;

	hp = 60;
	speed = 60;
	exp = 15;
	damage = 15;
	defence = 3;
}

SkeletonWarrior::~SkeletonWarrior()
{
	delete collider;
	delete skin_run;

	TEXTURE->DeleteTexture(L"SkeletonWarrior.png");
}

void SkeletonWarrior::Init()
{
	this->collider->SetWorldPos(Vector2(RANDOM->Int(-1000, 1000), RANDOM->Int(-1000, 1000)));
	this->collider->isFilled = false;
	this->collider->scale = Vector2(40, 40);

	this->skin_run->SetParentRT(*this->collider);
	this->skin_run->maxFrame.x = 5;
	this->skin_run->maxFrame.y = 12;
	this->skin_run->scale.x = skin_run->imageSize.x / skin_run->maxFrame.x * 3.2;
	this->skin_run->scale.y = skin_run->imageSize.y / skin_run->maxFrame.y * 3.2;
	this->skin_run->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
}

void SkeletonWarrior::Update()
{
	Monster::Update();

	switch (this->dir)
	{
	case MONSTER_DIRECTION::U: this->skin_run->frame.y = 0; break;
	case MONSTER_DIRECTION::D: this->skin_run->frame.y = 1; break;
	case MONSTER_DIRECTION::R: this->skin_run->frame.y = 2; break;
	case MONSTER_DIRECTION::L: this->skin_run->frame.y = 3; break;
	default: break;
	}
}

void SkeletonWarrior::Render()
{
	if (GM->DEBUG_MODE)
		this->collider->Render();
	this->skin_run->Render();
}