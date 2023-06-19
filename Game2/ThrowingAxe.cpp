#include "stdafx.h"
#include "Weapon.h"
#include "Projectile.h"
#include "Proj_axe.h"
#include "ThrowingAxe.h"

ThrowingAxe::ThrowingAxe()
{
    this->timeSinceLastTime = 0;

    this->name = "쓰로잉액스";
    this->attackSpeed = 1.1f;

    this->damage = 13.0f;
    this->critical = 0.1;

    this->range = 400.0f;
    this->projectileSpeed = 350.f;
}

bool ThrowingAxe::Attack()
{
    float currentTime = TIMER->GetWorldTime();
    float elapsedTime = currentTime - lastShotTime;

    if (elapsedTime >= this->timeSinceLastTime)
    {
        // 총구 위치 계산
        Vector2 muzzle = Vector2(
            GM->player->getColliderWeapon()->GetWorldPos()
            + GM->player->getColliderWeapon()->GetRight() * GM->player->getColliderWeapon()->scale.x);

        // 탄생성
        Proj_axe* throwingAxe = new Proj_axe
        (
            muzzle,
            GM->player->getColliderWeapon()->GetRight(),
            this->projectileSpeed,
            this->range,
            this->damage
        );

        //벡터에 탄 push
        GM->player->getProjectiles().emplace_back(throwingAxe);

        // 공속계산
        this->lastShotTime = currentTime;
        this->timeSinceLastTime = 1.0f / this->attackSpeed;
    }

    return false;
}

