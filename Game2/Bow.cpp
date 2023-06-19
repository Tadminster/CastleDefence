#include "stdafx.h"
#include "Item.h"
#include "Weapon.h"
#include "Projectile.h"
#include "Proj_arrow.h"
#include "Bow.h"

Bow::Bow()
{
    this->skin = new ObImage(L"Item_bow.png");
    this->tag = Tag::WEAPON;

    this->timeSinceLastTime = 0;

    this->name = L"    활";
    this->explain = L"화살을 날려 적에게 피해를 줍니다.";
    this->attackSpeed = 0.8f;

    this->damage = 10.0f;
    this->critical = 0.1;

    this->range = 400.0f;
    this->projectileSpeed = 400.f;

    this->level = 0;
    this->maxLevel = 10;
}

bool Bow::Attack()
{
    float currentTime = TIMER->GetWorldTime();
    float elapsedTime = currentTime - lastShotTime;

    if (elapsedTime >= this->timeSinceLastTime)
    {
        // 총구 위치 계산
        Vector2 muzzle = Vector2(
            GM->player->getColliderWeapon()->GetWorldPos()
            + GM->player->getColliderWeapon()->GetRight() * GM->player->getColliderWeapon()->scale.x);
        // 탄각 계산(플레이어가 바라보는 방향)
        // float rotation_z{ atan2f(shooter->get_right().y, shooter->get_right().x) };

        // 탄생성
        Proj_arrow* arrow = new Proj_arrow
        (
            muzzle,
            GM->player->getColliderWeapon()->GetRight(),
            this->projectileSpeed,
            this->range,
            this->damage
        );

        //벡터에 탄 push
        GM->player->getProjectiles().emplace_back(arrow);

        // 공속계산
        this->lastShotTime = currentTime;
        this->timeSinceLastTime = 1.0f / this->attackSpeed;
    }

    return false;
}

