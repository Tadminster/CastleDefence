#include "stdafx.h"
#include "Projectile.h"

Projectile::Projectile
(
    Vector2 spawnPos,
    Vector2 dir,
    float speed,
    float range,
    float damage
) :
    collider(new ObRect()),
    skin(nullptr),
    dir(dir),
    speed(speed),
    range(range),
    damage(damage),
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
    for (auto& enemy : GM->monster->getEnemy())
    {
        if (enemy->getCollider()->Intersect(collider))
        {
            cout << "collide" << endl;

            enemy->actionsWhenDamaged(Vector4(-damage, shove, 0, 0));
            return true;
        }
    }

    return false;
}
