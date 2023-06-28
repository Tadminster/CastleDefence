#include "stdafx.h"
#include "Projectile.h"
#include "Proj_enemyBullet.h"
#include "SkeletoneMage.h"

SkeletoneMage::SkeletoneMage()
{
	collider = new ObRect();
	skin_run = new ObImage(L"SkeletonMage.png");
	skin_runShadow = new ObImage(L"SkeletonMage.png");
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
	delete skin_runShadow;
	for (auto& range : range)
		delete range;

	TEXTURE->DeleteTexture(L"SkeletonMage.png");
}

void SkeletoneMage::Init()
{
	collider->pivot = OFFSET_B;
	collider->SetWorldPos(Vector2(RANDOM->Int(-1000, 1000), RANDOM->Int(-1000, 1000)));
	collider->isFilled = false;
	collider->scale = Vector2(40, 50);

	skin_run->SetParentRT(*collider);
	skin_run->pivot = OFFSET_B;
	skin_run->SetLocalPosY(-5);
	skin_run->maxFrame.x = 4;
	skin_run->maxFrame.y = 4;
	skin_run->scale.x = skin_run->imageSize.x / skin_run->maxFrame.x * 4;
	skin_run->scale.y = skin_run->imageSize.y / skin_run->maxFrame.y * 4;
	skin_run->ChangeAnim(ANIMSTATE::LOOP, 0.2f);

	skin_runShadow->SetParentRT(*collider);
	skin_runShadow->pivot = OFFSET_B;
	skin_runShadow->maxFrame.x = 4;
	skin_runShadow->maxFrame.y = 4;
	skin_runShadow->scale.x = skin_runShadow->imageSize.x / skin_runShadow->maxFrame.x * 4;
	skin_runShadow->scale.y = skin_runShadow->imageSize.y / skin_runShadow->maxFrame.y * 4;
	skin_runShadow->rotation.x = 80 * ToRadian;
	skin_runShadow->color = Vector4(0, 0, 0, 0.25);
	skin_runShadow->ChangeAnim(ANIMSTATE::LOOP, 0.2f);

	for (auto& range : range)
	{
		range->SetParentRT(*collider);
		range->isFilled = false;
	}
	range[0]->scale = Vector2(500, 500);
	range[1]->scale = Vector2(1000, 1000);
}

void SkeletoneMage::Update()
{
	// 몬스터 방향 설정
	 setDirection();
	//{
	//	Vector2 targetPos = GM->player->getPos();
	//	float diffX = targetPos.x - collider->GetWorldPos().x;
	//	float diffY = targetPos.y - collider->GetWorldPos().y;

	//	float dirX = diffX > 0 ? 1 : -1;
	//	float dirY = diffY > 0 ? 1 : -1;

	//	diffX = abs(diffX);
	//	diffY = abs(diffY);

	//	if (diffX * 3 < diffY)
	//	{
	//		if (dirY == -1)
	//			dir = MONSTER_DIRECTION::U;
	//		else if (dirY == 1)
	//			dir = MONSTER_DIRECTION::D;
	//	}
	//	else if (targetPos.x < collider->GetWorldPos().x)
	//	{
	//		dir = MONSTER_DIRECTION::L;
	//	}
	//	else if (targetPos.x > collider->GetWorldPos().x)
	//	{
	//		dir = MONSTER_DIRECTION::R;
	//	}

	//}

	if (action == MONSTER_ACTION::IDLE)
	{
		skin_run->ChangeAnim(ANIMSTATE::STOP, 0.0f);
		skin_runShadow->ChangeAnim(ANIMSTATE::STOP, 0.0f);
		skin_run->frame.x = 0;
		skin_runShadow->frame.x = 0;
	}
	else if (action == MONSTER_ACTION::RUN)
	{
		skin_run->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
		skin_runShadow->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
	}

	// 몬스터 상태에 따른 작동
	if (status == MONSTER_STATUS::NORMAL)
	{
		// 컬러 정상화
		if (skin_run->color.x != 0.5)
			skin_run->color = Vector4(0.5, 0.5, 0.5, 0.5);

		// 플레이어와 거리 계산
		Vector2 target = GM->player->getCollider()->GetWorldPos();
		float distance = (target - collider->GetWorldPos()).Length();
		ImGui::Text("distance %f\n", distance);

		// 거리가 250 보다 가까우면 도망, 500 보다 멀면 추격
		if (distance < 250)
		{
			action = MONSTER_ACTION::RUN;
			runAway();
		}
		else if (distance > 500)
		{
			action = MONSTER_ACTION::RUN;
			trace();
		}
		else
		{
			action = MONSTER_ACTION::IDLE;
			attack();
		}



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

	switch (dir)
	{
	case MONSTER_DIRECTION::U:
		skin_run->frame.y = 0;
		skin_runShadow->frame.y = 0;
		break;
	case MONSTER_DIRECTION::D:
		skin_run->frame.y = 1;
		skin_runShadow->frame.y = 1;
		break;
	case MONSTER_DIRECTION::R:
		skin_run->frame.y = 2;
		skin_runShadow->frame.y = 2;
		break;
	case MONSTER_DIRECTION::L:
		skin_run->frame.y = 3;
		skin_runShadow->frame.y = 3;
		break;
	default: break;
	}

	collider->Update();
	skin_run->Update();
	skin_runShadow->Update();
	for (auto& range : range)
		range->Update();
}

void SkeletoneMage::Render()
{
	if (GM->DEBUG_MODE)
	{
		for (auto& range : range)
			range->Render();
		collider->Render();
	}
	skin_runShadow->Render();
	skin_run->Render();
}

void SkeletoneMage::attack()
{
	static float timeSinceLastTime = 0.0f;
	static float lastShotTime;

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
			damage,
			1
		);

		//벡터에 탄 push
		GM->monster->getProjectiles().emplace_back(bullet);

		// 공속계산
		lastShotTime = currentTime;
		timeSinceLastTime = 1.0f / attackSpeed;
	}
}


