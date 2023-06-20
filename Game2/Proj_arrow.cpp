#include "stdafx.h"
#include "Projectile.h"
#include "Proj_arrow.h"

Proj_arrow::Proj_arrow(
	Vector2 spawnPos,
	Vector2 dir,
	float speed,
	float range,
	float damage,
	int   penetration)
{
	this->tag = DamageType::NORMAL;

	this->collider = new ObRect();
	this->collider->SetWorldPos(spawnPos);
	this->collider->scale = Vector2(16, 16);
	this->collider->isFilled = false;

	this->skin = new ObImage(L"proj_arrowShort.png");
	this->skin->SetParentRT(*this->collider);
	this->skin->maxFrame.x = 2;
	this->skin->maxFrame.y = 2;
	this->skin->frame.y = 1;
	this->skin->scale.x = 32;
	this->skin->scale.y = 32;
	this->skin->rotation.z = atanf(dir.y / dir.x);
	if (dir.x < 0) this->skin->reverseLR = true;

	this->dir = dir;
	this->speed = speed;
	this->range = range;
	this->damage = damage;
	this->penetration = penetration;
	this->traveledDistance = 0.f;
	this->shove = 350;
}

void Proj_arrow::Update()
{
	static float frameTick = 0.0f;
	if (TIMER->GetTick(frameTick, 0.05f))
	{
		skin->frame.x++;
	}

	Projectile::Update();
}

void Proj_arrow::Render()
{
	Projectile::Render();
}
