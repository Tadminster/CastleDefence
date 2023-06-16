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
	this->skin = new ObImage(L"Axe.png");
	this->skin->SetParentRT(*this->collider);
	this->skin->maxFrame.x = 4;
	this->skin->maxFrame.y = 2;
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
	skin->frame.x++;
	if (skin->frame.x == skin->maxFrame.x)
	{
		skin->frame.y++;
	}

	Projectile::Update();
}

void Proj_axe::Render()
{
	Projectile::Render();
}
