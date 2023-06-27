#include "stdafx.h"
#include "Item.h"
#include "Weapon.h"
#include "Projectile.h"
#include "Proj_fireball.h"
#include "Fireball.h"

Fireball::Fireball()
{
    this->skin = new ObImage(L"Item_fireball.png");
    this->tag = Tag::WEAPON;

    this->timeSinceLastTime = 0;

	this->damage = 10.0f;
	this->attackSpeed = 0.6f;
	this->critical = 0.1;
    this->penetration = 1;
    this->range = 400.0f;
    this->explosionRange = 80.f;
    this->projectileSpeed = 400.f;

    this->level = 0;
    this->maxLevel = 10;

	this->name = L" 파이어볼";
    std::wstringstream ss;
    ss << L"불덩이를 날려 적에게 피해를 줍니다. 주변에 50%의 폭발 피해를 가합니다. \n\n공격력: " << this->damage <<
        L"\n공격 속도: " << this->attackSpeed <<
        L"\n사정거리: " << this->range <<
        L"\n폭발범위: " << this->explosionRange;
    this->explain = ss.str();
}

void Fireball::Update()
{
    this->damage = 12.0f + level * 2;
    this->attackSpeed = 0.7f + level * 0.15;
    this->explosionRange = 80.f + level * 15;

    std::wstringstream ss;
    ss << L"불덩이를 날려 적에게 피해를 줍니다. 주변에 50%의 폭발 피해를 가합니다. \n\n공격력: " << this->damage <<
        L"\n공격 속도: " << this->attackSpeed <<
        L"\n사정거리: " << this->range <<
        L"\n폭발범위: " << this->explosionRange;
    this->explain = ss.str();
}

bool Fireball::Attack()
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
        Proj_fireball* fireball = new Proj_fireball
        (
            muzzle,
            GM->player->getColliderWeapon()->GetRight(),
            this->projectileSpeed,
            this->range,
            this->damage * GM->player->getDamage(),
            this->penetration,
            this->explosionRange
        );

        //벡터에 탄 push
        GM->player->getProjectiles().emplace_back(fireball);

        // 공속계산
        this->lastShotTime = currentTime;
        this->timeSinceLastTime = 1.0f / (this->attackSpeed * GM->player->getAttSpeed());
    }

    return false;
}

