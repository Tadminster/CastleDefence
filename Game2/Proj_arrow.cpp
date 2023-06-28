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
	tag = DamageType::NORMAL;

	collider = new ObRect();
	collider->SetWorldPos(spawnPos);
	collider->scale = Vector2(16, 16);
	collider->isFilled = false;

	skin = new ObImage(L"proj_arrowShort.png");
	skin->SetParentRT(*collider);
	skin->maxFrame.x = 2;
	skin->maxFrame.y = 2;
	skin->frame.y = 1;
	skin->scale.x = 32;
	skin->scale.y = 32;
	skin->rotation.z = atanf(dir.y / dir.x);
	skin->ChangeAnim(ANIMSTATE::LOOP, 0.05f);
	if (dir.x < 0) skin->reverseLR = true;

	this->dir = dir;
	this->speed = speed;
	this->range = range;
	this->damage = damage;
	this->penetration = penetration;
	traveledDistance = 0.f;
	shove = 350;
}

void Proj_arrow::Update()
{
	Projectile::Update();
}

void Proj_arrow::Render()
{
	Projectile::Render();
}
