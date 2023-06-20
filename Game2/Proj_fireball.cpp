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
	this->tag = DamageType::EXPLOSION;

	this->collider = new ObRect();
	this->collider->SetWorldPos(spawnPos);
	this->collider->scale = Vector2(16, 16);
	this->collider->isFilled = false;

	this->collider_range = new ObCircle();
	this->collider_range->SetParentRT(*this->collider);
	this->collider_range->scale.x = explosionRange;
	this->collider_range->scale.y = explosionRange;
	this->collider_range->isFilled = false;

	this->skin = new ObImage(L"proj_fireball.png");
	this->skin->SetParentRT(*this->collider);
	this->skin->maxFrame.x = 5;
	this->skin->maxFrame.y = 1;
	this->skin->scale.x = 32;
	this->skin->scale.y = 24;
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

void Proj_fireball::Update()
{
	ImGui::Text("rotation.z = %f", skin->rotation.z);
	ImGui::Text("dir.x = %f", dir.x);
	ImGui::Text("dir.y = %f", dir.y);

	this->skin->frame.x++;
	Projectile::Update();
	this->collider_range->Update();
}

void Proj_fireball::Render()
{
	Projectile::Render();
	if (DEBUG_MODE)
		this->collider_range->Render();
}
