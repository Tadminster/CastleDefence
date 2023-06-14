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

	// 몬스터 방향 설정
	Vector2 targetPos = GM->player->getPos();
	float diffX = targetPos.x - collider->GetWorldPos().x;
	float diffY = targetPos.y - collider->GetWorldPos().y;

	float dirX = diffX > 0 ? 1 : -1;
	float dirY = diffY > 0 ? 1 : -1;

	diffX = abs(diffX);
	diffY = abs(diffY);

	if (diffX * 3 < diffY)
	{
		if (dirY == -1)
			this->dir = MonsterDir::U;
		else if (dirY == 1)
			this->dir = MonsterDir::D;
	}
	else if (targetPos.x < collider->GetWorldPos().x)
	{
		this->dir = MonsterDir::L;
	}
	else if (targetPos.x > collider->GetWorldPos().x)
	{
		this->dir = MonsterDir::R;
	}

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

void Monster::SetHP(int value)
{
	this->hp = hp + value > 0 ? hp + value : 0;
}
