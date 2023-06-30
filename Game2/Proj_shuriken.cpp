#include "stdafx.h"
#include "Projectile.h"
#include "Proj_shuriken.h"

Proj_shuriken::Proj_shuriken(
	Vector2 spawnPos,
	Vector2 dir,
	float speed,
	float range,
	float damage,
	int   penetration)
{
	tag = DamageType::NORMAL;

	collider = new ObRect();
	collider->SetWorldPos(spawnPos);
	collider->scale = Vector2(16, 16);
	collider->isFilled = false;

    collider_range = new ObCircle();
    collider_range->SetParentRT(*collider);
    collider_range->scale.x = 500;
    collider_range->scale.y = 500;
    collider_range->isFilled = false;

	skin = new ObImage(L"proj_shuriken.png");
	skin->SetParentRT(*collider);
	skin->maxFrame.x = 1;
	skin->maxFrame.y = 1;
	skin->frame.y = 1;
	skin->scale.x = 32;
	skin->scale.y = 32;
	skin->rotation.z = atanf(dir.y / dir.x);
	skin->ChangeAnim(ANIMSTATE::LOOP, 0.05f);
	if (dir.x < 0) skin->reverseLR = true;

	this->dir = dir;
	this->speed = speed;
	this->range = range;
	this->damage = damage;
	this->penetration = penetration;
	traveledDistance = 0.f;
	shove = 350;
}

void Proj_shuriken::Update()
{
    collider_range->Update();
	Projectile::Update();
}

void Proj_shuriken::Render()
{
    collider_range->Render();
	Projectile::Render();
}

bool Proj_shuriken::hasCollideWithMonster()
{

    // 모든 몬스터를 순회
    for (auto& enemy : GM->monster->getEnemy())
    {
        // 몬스터가 발사체와 충돌했으면
        if (enemy->getCollider()->Intersect(this->collider))
        {
            // 이전에 충돌한적이 있는지 비교
            for (auto& crashed : crash)
                if (crashed == enemy) return false;

            // 없으면 새 충돌벡터에 추가
            this->crash.emplace_back(enemy);
            // 남은 관통횟수 -1
            this->penetration--;

            // 충돌 이펙트
            AfterEffect();

            // 몬스터 데미지 액션
            enemy->actionsWhenDamaged(Vector4(-damage, shove, 0, 0));

            // 새 타겟 탐색
            findNewTarget();

            // 남은 관통력 반환
            if (penetration > 0) return false;
            else return true;
        }
    }

    return false;
}

void Proj_shuriken::findNewTarget()
{
    cout << "-----------------------------------" << endl;

    float minDistance = range / 2.0f;
    Vector2 nextDir = dir;

    // 모든 몬스터를 순회
    for (auto& enemy : GM->monster->getEnemy())
    {
        // 이전에 충돌한적이 있는지 비교
        for (auto& crashed : crash)
            if (crashed == enemy)
            {
                
            }
            else
            {
                // 거리 계산
                Vector2 newDir = enemy->getCollider()->GetWorldPos() - this->collider->GetWorldPos();
                float newDistance = newDir.Length();



                // 계산한 거리가 더 짧으면 거리와 방향 저장
                if (minDistance > newDistance)
                {
                    cout << "이전거리: " << minDistance << endl;
                    cout << "탐색거리: " << newDistance << endl;

                    minDistance = newDistance;
                    nextDir = newDir;
                }
            }

  
    }

    cout << "이전방향_x: " << dir.x << endl;
    cout << "이전방향_y: " << dir.y << endl;
    cout << "탐색방향_x: " << nextDir.x << endl;
    cout << "탐색방향_y: " << nextDir.x << endl << endl;

    traveledDistance = 0.0f;
    dir = nextDir;
    dir.Normalize();
}
