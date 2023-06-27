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

    this->damage = 7.0f;
    this->attackSpeed = 0.7f;
    this->critical = 0.1;
    this->penetration = 2;
    this->range = 650.0f;
    this->projectileSpeed = 500.f;

    this->level = 0;
    this->maxLevel = 10;

    this->name = L"    활";
    //this->explain = L"화살을 날려 적에게 피해를 줍니다. \n\n공격력: 10 \n공격속도: 1.0 \n사정거리: 650";

    std::wstringstream ss;
    ss << L"화살을 날려 적에게 피해를 줍니다.\n\n공격력: " << this->damage <<
        L"\n공격 속도: " << this->attackSpeed <<
        L"\n사정거리: " << this->range <<
        L"\n관통력: " << this->penetration-1;
    this->explain = ss.str();
}

void Bow::Update()
{
    this->damage = 10.0f + level * 1;
    this->attackSpeed = 1.0f + level * 0.2;

    std::wstringstream ss;
    ss << L"화살을 날려 적에게 피해를 줍니다.\n\n공격력: " << this->damage <<
        L"\n공격 속도: " << this->attackSpeed <<
        L"\n사정거리: " << this->range <<
        L"\n관통력: " << this->penetration-1;
    this->explain = ss.str();
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
            this->damage * GM->player->getDamage(),
            this->penetration
        );

        //벡터에 탄 push
        GM->player->getProjectiles().emplace_back(arrow);

        // 공속계산
        this->lastShotTime = currentTime;
        this->timeSinceLastTime = 1.0f / (this->attackSpeed * GM->player->getAttSpeed());
    }

    return false;
}

