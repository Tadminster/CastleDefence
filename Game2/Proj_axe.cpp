#include "stdafx.h"
#include "Projectile.h"
#include "Proj_axe.h"

Proj_axe::Proj_axe(
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

	skin = new ObImage(L"proj_axe.png");
	skin->SetParentRT(*collider);
	skin->maxFrame.x = 8;
	skin->maxFrame.y = 1;
	skin->scale.x = 32;
	skin->scale.y = 32;
	skin->ChangeAnim(ANIMSTATE::LOOP, 0.05f);

	this->dir = dir;
	this->speed = speed;
	this->range = range;
	this->damage = damage;
	this->penetration = penetration;
	traveledDistance = 0.f;
	shove = 350;
}

void Proj_axe::Update()
{
	Projectile::Update();
}

void Proj_axe::Render()
{
	Projectile::Render();
}
