#include "stdafx.h"
#include "SkeletoneMage.h"

SkeletoneMage::SkeletoneMage()
{
	this->collider = new ObRect();
	this->skin_run = new ObImage(L"SkeletonMage.png");

	hp = 200;
	speed = 50;
	exp = 100;
	damage = 20;
	defence = 2;
}

SkeletoneMage::~SkeletoneMage()
{
	delete collider;
	delete skin_run;

	TEXTURE->DeleteTexture(L"SkeletonMage.png");
}

void SkeletoneMage::Init()
{
	this->collider->SetWorldPos(Vector2(RANDOM->Int(-1000, 1000), RANDOM->Int(-1000, 1000)));
	this->collider->isFilled = false;
	this->collider->scale = Vector2(40, 40);

	this->skin_run->SetParentRT(*this->collider);
	this->skin_run->maxFrame.x = 4;
	this->skin_run->maxFrame.y = 4;
	this->skin_run->scale.x = skin_run->imageSize.x / skin_run->maxFrame.x * 4;
	this->skin_run->scale.y = skin_run->imageSize.y / skin_run->maxFrame.y * 4;
	this->skin_run->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
}

void SkeletoneMage::Update()
{
	Vector2 target = GM->player->getCollider()->GetWorldPos();
	float distance = (target - this->collider->GetWorldPos()).Length();
	ImGui::Text("distance %f\n", distance);
	if (distance > 300)
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

void SkeletoneMage::Render()
{
	if (GM->DEBUG_MODE)
		this->collider->Render();
	this->skin_run->Render();
}


