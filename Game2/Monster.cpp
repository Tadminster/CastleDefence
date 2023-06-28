#include "stdafx.h"
#include "Monster.h"

Monster::Monster() :
	collider(new ObRect()), 
	skin_run(nullptr),
	dir(MONSTER_DIRECTION::D),
	status(MONSTER_STATUS::NORMAL),
	hp(1), speed(10), damage(1), exp(1), timeOfDamage(0)
	{}

void Monster::Init()
{
}

void Monster::Update()
{
	// 몬스터 방향 설정
	{
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
				this->dir = MONSTER_DIRECTION::U;
			else if (dirY == 1)
				this->dir = MONSTER_DIRECTION::D;
		}
		else if (targetPos.x < collider->GetWorldPos().x)
		{
			this->dir = MONSTER_DIRECTION::L;
		}
		else if (targetPos.x > collider->GetWorldPos().x)
		{
			this->dir = MONSTER_DIRECTION::R;
		}

		this->collider->Update();
		if (this->skin_run)
			this->skin_run->Update();
	}

	// 몬스터 상태에 따른 작동
	if (status == MONSTER_STATUS::NORMAL)
	{
		// 컬러 정상화
		if (skin_run || skin_run->color.x != 0.5)
			skin_run->color = Vector4(0.5, 0.5, 0.5, 0.5);

		// 다가가기
		if (action == MONSTER_ACTION::RUN)
			trace();
	}
	else if (status == MONSTER_STATUS::DAMAGED)
	{
		// 미니언이나 엘리트 일경우 넉백
		if (type == MONSTER_TYPE::MINION || type == MONSTER_TYPE::ELITE)
			knockBack();

		// 0.05초 후에 노말 상태로
		if (timeOfDamage + 0.05f < TIMER->GetWorldTime())
		{
			knockBackFactor = 0;
			status = MONSTER_STATUS::NORMAL;
		}
	}
}

void Monster::Render()
{
	if (GM->DEBUG_MODE)
		this->collider->Render();

	if (this->skin_run)
		this->skin_run->Render();
}

void Monster::trace()
{
	// 플레이어가 있는 방향
	Vector2 dirVec = (GM->player->getPos() - collider->GetWorldPos());
	dirVec.Normalize();
	this->collider->MoveWorldPos(dirVec * speed * DELTA);
}

void Monster::runAway()
{
	// 플레이어가 있는 방향
	Vector2 dirVec = (collider->GetWorldPos() -  GM->player->getPos());
	dirVec.Normalize();
	this->collider->MoveWorldPos(dirVec * speed * DELTA);

}

void Monster::knockBack()
{
	// 플레이어의 반대방향
	Vector2 knockBackDir = this->collider->GetWorldPos() - GM->player->getPos();
	knockBackDir.Normalize();
	this->collider->MoveWorldPos(knockBackDir * knockBackFactor * DELTA);
}

void Monster::attack()
{
}

void Monster::setHP(int value)
{
	this->hp = max(hp + value, 0);
}

void Monster::setStatus(int type)
{
	if (type == 0)
		status = MONSTER_STATUS::NORMAL;
	else if (type == 1)
		status = MONSTER_STATUS::DAMAGED;
}


void Monster::actionsWhenDamaged(Vector4 value)
{
	// 상태를 데미지 받음으로 변경
	status = MONSTER_STATUS::DAMAGED;
	// 데미지 받은 시간 기록
	timeOfDamage = TIMER->GetWorldTime();
	// 스킨 컬러 변경
	if (skin_run)
		skin_run->color = Vector4(1, 1, 1, 0.5);
	// 체력 감소
	this->hp = max(hp + value.x, 0);
	// 넉백 계수
	knockBackFactor = value.y;
}
