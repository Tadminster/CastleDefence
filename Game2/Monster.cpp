#include "stdafx.h"
#include "Monster.h"

Monster::Monster() :
	collider(new ObRect()), 
	skin_run(nullptr),
	dir(MonsterDir::D)
	{}

void Monster::Init()
{
}

void Monster::Update()
{
	this->Trace();
	this->collider->Update();

	if (this->skin_run)
		this->skin_run->Update();
}

void Monster::Render()
{
	this->collider->Render();

	if (this->skin_run)
		this->skin_run->Render();
}

void Monster::Trace()
{
	// 플레이어가 있는 방향
	Vector2 dirVec = (GM->player->getPos() - collider->GetWorldPos());
	dirVec.Normalize();
	this->collider->MoveWorldPos(dirVec * speed * DELTA);
}
