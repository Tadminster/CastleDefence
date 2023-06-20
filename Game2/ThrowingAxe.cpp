#include "stdafx.h"
#include "Item.h"
#include "Weapon.h"
#include "Projectile.h"
#include "Proj_axe.h"
#include "ThrowingAxe.h"

ThrowingAxe::ThrowingAxe()
{
    this->skin = new ObImage(L"Item_axe.png");
    this->tag = Tag::WEAPON;

    this->timeSinceLastTime = 0;

    this->damage = 15.0f;
    this->attackSpeed = 0.7f;
    this->critical = 0.1;
    this->penetration = 1;
    this->range = 300.0f;
    this->projectileSpeed = 350.f;

    this->level = 0;
    this->maxLevel = 10;

    this->name = L" 쓰로잉액스";
    //this->explain = L"도끼를 던져 적에게 피해를 줍니다.\n\n공격력: 15 \n공격속도: 0.7 \n사정거리: 300";

    std::wstringstream ss;
    ss << L"도끼를 날려 적에게 피해를 줍니다.\n\n공격력: " << this->damage <<
        L"\n공격 속도: " << this->attackSpeed <<
        L"\n사정거리: " << this->range;
    this->explain = ss.str();
}

void ThrowingAxe::Update()
{
    this->damage = 15.0f + level * 4;
    this->attackSpeed = 0.7f + level * 0.1;

    std::wstringstream ss;
    ss << L"도끼를 날려 적에게 피해를 줍니다.\n\n공격력: " << this->damage <<
        L"\n공격 속도: " << this->attackSpeed <<
        L"\n사정거리: " << this->range;
    this->explain = ss.str();
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
            this->damage * GM->player->getDamage(),
            this->penetration
        );

        //벡터에 탄 push
        GM->player->getProjectiles().emplace_back(throwingAxe);

        // 공속계산
        this->lastShotTime = currentTime;
        this->timeSinceLastTime = 1.0f / (this->attackSpeed * GM->player->getAttSpeed());
    }

    return false;
}

