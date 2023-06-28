#include "stdafx.h"
#include "Projectile.h"
#include "Proj_fireball.h"

Proj_fireball::Proj_fireball(
	Vector2 spawnPos,
	Vector2 dir,
	float speed,
	float range,
	float damage,
	int   penetration,
	float explosionRange)
{
	tag = DamageType::EXPLOSION;

	collider = new ObRect();
	collider->SetWorldPos(spawnPos);
	collider->scale = Vector2(16, 16);
	collider->isFilled = false;

	collider_range = new ObCircle();
	collider_range->SetParentRT(*collider);
	collider_range->scale.x = explosionRange;
	collider_range->scale.y = explosionRange;
	collider_range->isFilled = false;

	skin = new ObImage(L"proj_fireball.png");
	skin->SetParentRT(*collider);
	skin->maxFrame.x = 5;
	skin->maxFrame.y = 1;
	skin->scale.x = 32;
	skin->scale.y = 24;
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

void Proj_fireball::Update()
{
	Projectile::Update();
	collider_range->Update();
}

void Proj_fireball::Render()
{
	Projectile::Render();
	if (GM->DEBUG_MODE)
		collider_range->Render();
}

void Proj_fireball::AfterEffect()
{
	ObImage* afterImg = new ObImage(L"fireball_explosion.png");
	afterImg->SetWorldPos(collider->GetWorldPos());
	afterImg->maxFrame.x = 7;
	afterImg->maxFrame.y = 1;
	afterImg->scale.x = collider_range->scale.x;
	afterImg->scale.y = collider_range->scale.y;
	afterImg->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	afterImg->color.w = 0.4f;

	GM->afterEffectManager.emplace_back(afterImg);
}
