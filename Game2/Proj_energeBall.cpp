#include "stdafx.h"
#include "Projectile.h"
#include "Proj_energeBall.h"

Proj_energeBall::Proj_energeBall(
	Vector2 spawnPos,
	Vector2 dir,
	float speed,
	float range,
	float damage,
	int   penetration)
{
	tag = DamageType::NORMAL;

	collider = new ObRect();
	collider->SetParentRT(*GM->player->getCollider());
	collider->SetWorldPos(spawnPos);
	collider->SetLocalPosX(100);
	collider->scale = Vector2(16, 16);
	collider->isFilled = false;

	skin = new ObImage(L"proj_energeBall.png");
	skin->SetParentRT(*collider);
	skin->maxFrame.x = 22;
	skin->maxFrame.y = 1;
	skin->frame.y = 1;
	skin->scale.x = skin->imageSize.x / skin->maxFrame.x;
	skin->scale.y = skin->imageSize.y / skin->maxFrame.y;
	skin->ChangeAnim(ANIMSTATE::LOOP, 0.05f);

	this->dir = dir;
	this->speed = speed;
	this->range = range;
	this->damage = damage;
	this->penetration = penetration;
	traveledDistance = 0.f;
	shove = 350;
}

void Proj_energeBall::Update()
{
	//static float rotationInterval = 0.0f;
	//if (TIMER->GetTick(rotationInterval, 0.05f))
		collider->rotation2.z += 0.1 * ToRadian;

	collider->Update();
	skin->Update();
	
}

void Proj_energeBall::Render()
{
	Projectile::Render();
}
