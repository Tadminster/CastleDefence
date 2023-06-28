#include "stdafx.h"
#include "MegaSlime.h"

MegaSlime::MegaSlime()
{
	collider = new ObRect();
	skin_run = new ObImage(L"MegaSlimeBlue.png");
	skin_runShadow = new ObImage(L"MegaSlimeBlue.png");

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
	delete skin_runShadow;

	TEXTURE->DeleteTexture(L"MegaSlimeBlue.png");
}

void MegaSlime::Init()
{
	collider->pivot = OFFSET_B;
	collider->SetWorldPos(Vector2(RANDOM->Int(-1000, 1000), RANDOM->Int(-1000, 1000)));
	collider->isFilled = false;
	collider->scale = Vector2(35, 35);

	skin_run->SetParentRT(*collider);
	skin_run->pivot = OFFSET_B;
	skin_run->SetLocalPosY(-10);
	skin_run->maxFrame.x = 7;
	skin_run->maxFrame.y = 4;
	skin_run->scale.x = skin_run->imageSize.x / skin_run->maxFrame.x * 4;
	skin_run->scale.y = skin_run->imageSize.y / skin_run->maxFrame.y * 4;
	skin_run->ChangeAnim(ANIMSTATE::LOOP, 0.2f);

	skin_runShadow->SetParentRT(*collider);
	skin_runShadow->pivot = OFFSET_B;
	skin_runShadow->maxFrame.x = 7;
	skin_runShadow->maxFrame.y = 4;
	skin_runShadow->scale.x = skin_runShadow->imageSize.x / skin_runShadow->maxFrame.x * 4;
	skin_runShadow->scale.y = skin_runShadow->imageSize.y / skin_runShadow->maxFrame.y * 4;
	skin_runShadow->rotation.x = 80 * ToRadian;
	skin_runShadow->color = Vector4(0, 0, 0, 0.25);
	skin_runShadow->ChangeAnim(ANIMSTATE::LOOP, 0.2f);

}

void MegaSlime::Update()
{

	// 점프모션에만 이동
	if (skin_run->frame.x > 1) action = MONSTER_ACTION::RUN;
	else action = MONSTER_ACTION::IDLE;


	switch (action)
	{
	case MONSTER_ACTION::IDLE:
		//skin_run->frame.x = 0;
		break;
	case MONSTER_ACTION::RUN:
		if (skin_run->frame.x == 0)
			skin_run->frame.x++;
		else if (skin_run->frame.x == 2)
			skin_runShadow->color.w = 0.15;
		else if (skin_run->frame.x == 3)
			skin_runShadow->color.w = 0.10;
		else if (skin_run->frame.x == 4)
			skin_runShadow->color.w = 0.15;
		else if (skin_run->frame.x == 5)
			skin_runShadow->color.w = 0.25;
		break;
	case MONSTER_ACTION::DASH:
		break;
	default:
		break;
	}

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

void MegaSlime::Render()
{
	skin_runShadow->Render();
	skin_run->Render();
	if (GM->DEBUG_MODE)
		collider->Render();
}