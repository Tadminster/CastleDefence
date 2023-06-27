#include "stdafx.h"
#include "Projectile.h"
#include "Proj_enemyBullet.h"

Proj_enemyBullet::Proj_enemyBullet(
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

	this->skin = new ObImage(L"Bullet.png");
	this->skin->SetParentRT(*this->collider);
	this->skin->maxFrame.x = 30;
	this->skin->maxFrame.y = 1;
	this->skin->scale.x = this->skin->imageSize.x / this->skin->maxFrame.x * 2;
	this->skin->scale.y = this->skin->imageSize.y / this->skin->maxFrame.y * 2;
	this->skin->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
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

void Proj_enemyBullet::Update()
{
	Projectile::Update();
}

void Proj_enemyBullet::Render()
{
	Projectile::Render();
}
