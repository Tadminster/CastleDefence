#include "stdafx.h"
#include "Projectile.h"
#include "Proj_axe.h"

Proj_axe::Proj_axe(
	Vector2 spawnPos, 
	Vector2 dir, 
	float speed, 
	float range, 
	float damage)
{
	this->collider = new ObRect();
	this->collider->SetWorldPos(spawnPos);
	this->collider->scale = Vector2(16, 16);
	this->collider->isFilled = false;

	this->skin = new ObImage(L"proj_axe.png");
	this->skin->SetParentRT(*this->collider);
	this->skin->maxFrame.x = 8;
	this->skin->maxFrame.y = 1;
	this->skin->scale.x = 32;
	this->skin->scale.y = 32;

	this->dir = dir;
	this->speed = speed;
	this->range = range;
	this->damage = damage,
	this->traveledDistance = 0.f;
	this->shove = 350;
}

void Proj_axe::Update()
{
	static float frameTick = 0.0f;
	if (TIMER->GetTick(frameTick, 0.05f))
	{
		skin->frame.x++;
	}

	Projectile::Update();
}

void Proj_axe::Render()
{
	Projectile::Render();
}
