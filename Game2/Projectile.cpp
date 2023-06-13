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
    skin(nullptr),
    speed(speed),
    range(range),
    traveledDistance(0.f),
    damage(damage)
{
    this->scale.x = 10;
    this->scale.y = 10;
    this->isFilled = true;
}

void Projectile::Update()
{
    // V2_탄속만 적용
    Vector2 velocity = (this->dir * this->speed);

    this->MoveWorldPos(velocity * DELTA);
    ObRect::Update();

    // 탄이 이동한 거리 계산
    traveledDistance += std::sqrt(std::pow(speed * DELTA, 2) + std::pow(speed * DELTA, 2));
}
