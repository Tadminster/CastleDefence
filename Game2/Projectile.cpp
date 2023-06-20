#include "stdafx.h"
#include "Projectile.h"

Projectile::Projectile
(
    Vector2 spawnPos,
    Vector2 dir,
    float speed,
    float range,
    float damage,
    int   penetration
) :
    collider(new ObRect()),
    skin(nullptr),
    dir(dir),
    speed(speed),
    range(range),
    damage(damage),
    penetration(penetration),
    traveledDistance(0.f),
    shove(300)
{
    collider->rotation.z = atanf(dir.y / dir.x);
    collider->scale.x = 10;
    collider->scale.y = 10;
    collider->isFilled = false;
    collider->SetWorldPos(spawnPos);

    //skin->SetParentRT(*collider);
}

void Projectile::Update()
{
    // 발사체 이동
    Vector2 velocity = (this->dir * this->speed);
    collider->MoveWorldPos(velocity * DELTA);

    // 업데이트
    collider->Update();
    skin->Update();

    // 이동한 거리 계산
    traveledDistance += std::sqrt(std::pow(speed * DELTA, 2) + std::pow(speed * DELTA, 2));
}

void Projectile::Render()
{
    skin->Render();

    if (DEBUG_MODE)
        collider->Render();
}

bool Projectile::hasCollideWithMonster()
{
    // 모든 몬스터를 순회
    for (auto& enemy : GM->monster->getEnemy())
    {
        // 몬스터가 화살과 충돌했으면
        if (enemy->getCollider()->Intersect(this->collider))
        {
            // 이전에 충돌한적이 있는지 비교
            for (auto& crashed : crash)
                if (crashed == enemy) return false;

            cout << "new collide" << endl;
            this->crash.emplace_back(enemy);
            this->penetration--;
            cout << penetration << endl;

            enemy->actionsWhenDamaged(Vector4(-damage, shove, 0, 0));
            
            // 남은 관통력 반환
            if (penetration > 0) return false;
            else return true;
        }
    }

    return false;
}
