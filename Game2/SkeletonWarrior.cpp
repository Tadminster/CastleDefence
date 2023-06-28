#include "stdafx.h"
#include "SkeletonWarrior.h"

SkeletonWarrior::SkeletonWarrior()
{
	collider = new ObRect();
	skin_run = new ObImage(L"SkeletonWarrior.png");
	skin_runShadow = new ObImage(L"SkeletonWarrior.png");

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
	delete skin_runShadow;

	TEXTURE->DeleteTexture(L"SkeletonWarrior.png");
}

void SkeletonWarrior::Init()
{
	collider->pivot = OFFSET_B;
	collider->SetWorldPos(Vector2(RANDOM->Int(-1000, 1000), RANDOM->Int(-1000, 1000)));
	collider->isFilled = false;
	collider->scale = Vector2(40, 40);

	skin_run->SetParentRT(*collider);
	skin_run->pivot = OFFSET_B;
	skin_run->maxFrame.x = 5;
	skin_run->maxFrame.y = 12;
	skin_run->scale.x = skin_run->imageSize.x / skin_run->maxFrame.x * 3.2;
	skin_run->scale.y = skin_run->imageSize.y / skin_run->maxFrame.y * 3.2;
	skin_run->ChangeAnim(ANIMSTATE::LOOP, 0.2f);

	skin_runShadow->SetParentRT(*collider);
	skin_runShadow->pivot = OFFSET_B;
	skin_runShadow->maxFrame.x = 5;
	skin_runShadow->maxFrame.y = 12;
	skin_runShadow->scale.x = skin_runShadow->imageSize.x / skin_runShadow->maxFrame.x * 3.2;
	skin_runShadow->scale.y = skin_runShadow->imageSize.y / skin_runShadow->maxFrame.y * 3.2;
	skin_runShadow->rotation.x = 80 * ToRadian;
	skin_runShadow->color = Vector4(0, 0, 0, 0.25);
	skin_runShadow->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
}

void SkeletonWarrior::Update()
{
	setDirection();
	switch (dir)
	{
	case MONSTER_DIRECTION::U:
		skin_run->frame.y = 0;
		skin_runShadow->frame.y = 0;
		break;
	case MONSTER_DIRECTION::D:
		skin_run->frame.y = 1;
		skin_runShadow->frame.y = 1;
		break;
	case MONSTER_DIRECTION::R:
		skin_run->frame.y = 2;
		skin_runShadow->frame.y = 2;
		break;
	case MONSTER_DIRECTION::L:
		skin_run->frame.y = 3;
		skin_runShadow->frame.y = 3;
		break;
	default: break;
	}

	Monster::Update();
}

void SkeletonWarrior::Render()
{
	skin_runShadow->Render();
	skin_run->Render();
	if (GM->DEBUG_MODE)
		collider->Render();
}