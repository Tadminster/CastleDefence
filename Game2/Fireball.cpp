#include "stdafx.h"
#include "Weapon.h"
#include "Projectile.h"
#include "Fireball.h"

Fireball::Fireball()
{
    this->timeSinceLastTime = 0;

	this->name = "파이어볼";
	this->damage = 10.0f;
	this->attackSpeed = 2.0f;
	this->range = 500.0f;
	this->critical = 0.1;
}

bool Fireball::Attack()
{
    static float lastShotTime = 0;

    float currentTime = TIMER->GetWorldTime();
    float elapsedTime = currentTime - lastShotTime;

    if (elapsedTime >= this->timeSinceLastTime)
    {
        // 총구 위치 계산
        Vector2 muzzle = Vector2(
            GM->player->getColliderWeapon()->GetWorldPos() 
            + GM->player->getColliderWeapon()->GetRight() 
            * GM->player->getColliderWeapon()->scale.x);
        // 탄각 계산(플레이어가 바라보는 방향)
        // float rotation_z{ atan2f(shooter->get_right().y, shooter->get_right().x) };

        // 탄생성
        Projectile projectile
        (
            muzzle,
            GM->player->getColliderWeapon()->GetRight(),
            this->projectileSpeed,
            this->range,
            this->damage
        );

        //벡터에 탄 push
        GM->player->getProjectiles().emplace_back(projectile);

        // 공속계산
        this->lastShotTime = currentTime;
        this->timeSinceLastTime = 1.0f / this->attackSpeed;
    }

    return false;
}

