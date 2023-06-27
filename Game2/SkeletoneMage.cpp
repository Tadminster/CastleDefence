#include "stdafx.h"
#include "Projectile.h"
#include "Proj_enemyBullet.h"
#include "SkeletoneMage.h"

SkeletoneMage::SkeletoneMage()
{
	this->collider = new ObRect();
	this->skin_run = new ObImage(L"SkeletonMage.png");
	for (auto& range : range)
		range = new ObCircle();

	status = MONSTER_STATUS::NORMAL;
	action = MONSTER_ACTION::IDLE;
	dir = MONSTER_DIRECTION::D;
	type = MONSTER_TYPE::CHAMPION;

	hp = 200;
	damage = 20;
	defence = 2;
	
	speed = 50;
	attackSpeed = 0.4;

	exp = 100;
}

SkeletoneMage::~SkeletoneMage()
{
	delete collider;
	delete skin_run;
	for (auto& range : range)
		delete range;

	TEXTURE->DeleteTexture(L"SkeletonMage.png");
}

void SkeletoneMage::Init()
{
	this->collider->SetWorldPos(Vector2(RANDOM->Int(-1000, 1000), RANDOM->Int(-1000, 1000)));
	this->collider->isFilled = false;
	this->collider->scale = Vector2(40, 40);

	this->skin_run->SetParentRT(*this->collider);
	this->skin_run->maxFrame.x = 4;
	this->skin_run->maxFrame.y = 4;
	this->skin_run->scale.x = skin_run->imageSize.x / skin_run->maxFrame.x * 4;
	this->skin_run->scale.y = skin_run->imageSize.y / skin_run->maxFrame.y * 4;
	this->skin_run->ChangeAnim(ANIMSTATE::LOOP, 0.2f);

	for (auto& range : range)
	{
		range->SetParentRT(*this->collider);
		range->isFilled = false;
	}
	this->range[0]->scale = Vector2(500, 500);
	this->range[1]->scale = Vector2(1000, 1000);
}

void SkeletoneMage::Update()
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

		// 플레이어와 거리 계산
		Vector2 target = GM->player->getCollider()->GetWorldPos();
		float distance = (target - this->collider->GetWorldPos()).Length();
		ImGui::Text("distance %f\n", distance);

		// 거리가 250 보다 가까우면 도망, 500 보다 멀면 추격
		if (distance < 250) runAway();
		else if (distance > 500) trace();
		else attack();


	}
	else if (status == MONSTER_STATUS::DAMAGED)
	{
		// 0.05초 후에 노말 상태로
		if (timeOfDamage + 0.05f < TIMER->GetWorldTime())
		{
			knockBackFactor = 0;
			status = MONSTER_STATUS::NORMAL;
		}
	}

	switch (this->dir)
	{
	case MONSTER_DIRECTION::U: this->skin_run->frame.y = 0; break;
	case MONSTER_DIRECTION::D: this->skin_run->frame.y = 1; break;
	case MONSTER_DIRECTION::R: this->skin_run->frame.y = 2; break;
	case MONSTER_DIRECTION::L: this->skin_run->frame.y = 3; break;
	default: break;
	}

	for (auto& range : range)
		range->Update();
}

void SkeletoneMage::Render()
{
	if (GM->DEBUG_MODE)
	{
		for (auto& range : range)
			range->Render();
		this->collider->Render();
	}
	this->skin_run->Render();
}

void SkeletoneMage::attack()
{
	static float timeSinceLastTime = 0.0f;
	static float lastShotTime ;

	float currentTime = TIMER->GetWorldTime();
	float elapsedTime = currentTime - lastShotTime;

	if (elapsedTime >= timeSinceLastTime)
	{
		// 총구 위치 계산
		Vector2 muzzle = Vector2(
			GM->player->getColliderWeapon()->GetWorldPos()
			+ GM->player->getColliderWeapon()->GetRight() * GM->player->getColliderWeapon()->scale.x);
		// 탄각 계산(플레이어가 바라보는 방향)
		Vector2 dir = GM->player->getCollider()->GetWorldPos() - collider->GetWorldPos();
		dir.Normalize();

		// 탄생성
		Proj_enemyBullet* bullet = new Proj_enemyBullet
		(
			collider->GetWorldPos(),
			dir,
			200,
			1000,
			this->damage,
			1
		);

		//벡터에 탄 push
		GM->monster->getProjectiles().emplace_back(bullet);

		// 공속계산
		lastShotTime = currentTime;
		timeSinceLastTime = 1.0f / this->attackSpeed;
	}
}


