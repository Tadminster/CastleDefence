#include "stdafx.h"
#include "Item.h"
#include "Weapon.h"
#include "Projectile.h"
#include "Proj_energeBall.h"
#include "EnergeBall.h"

EnergeBall::EnergeBall()
{
    this->skin = new ObImage(L"item_energeBall.png");
    this->tag = Tag::WEAPON;

    this->timeSinceLastTime = 0;

    this->damage = 5.0f;
    this->attackSpeed = 0.1f;
    this->critical = 0.3;
    this->penetration = 3;
    this->range = 650.0f;
    this->projectileSpeed = 500.f;

    this->level = 0;
    this->maxLevel = 10;

    this->name = L" 에너지볼";

    std::wstringstream ss;
    ss << L"에너지볼을 생성해 주변을 회전하며 적을 공격합니다.\n\n공격력: " << this->damage <<
        L"\n공격 속도: " << this->attackSpeed <<
        L"\n사정거리: " << this->range <<
        L"\n관통력: " << this->penetration - 1;
    this->explain = ss.str();
}

void EnergeBall::Update()
{
    this->damage = 10.0f + level * 1;
    this->attackSpeed = 0.3f + level * 0.2;

    std::wstringstream ss;
    ss << L"에너지볼을 생성해 주변을 회전하며 적을 공격합니다.\n\n공격력: " << this->damage <<
        L"\n공격 속도: " << this->attackSpeed <<
        L"\n사정거리: " << this->range <<
        L"\n관통력: " << this->penetration - 1;
    this->explain = ss.str();
}

bool EnergeBall::Attack()
{
    float currentTime = TIMER->GetWorldTime();
    float elapsedTime = currentTime - lastShotTime;

    if (elapsedTime >= this->timeSinceLastTime)
    {
        cout << "currentTime " << currentTime << endl;
        cout << "elapsedTime " << elapsedTime << endl;
        cout << "timeSinceLastTime " << timeSinceLastTime << endl;
        cout << "attackSpeed " << attackSpeed << endl;
        cout << "player_attackSpeed " << GM->player->getAttSpeed() << endl << endl;

        // 탄생성
        Proj_energeBall* energeball = new Proj_energeBall
        (
            GM->player->getCollider()->GetWorldPos() ,
            GM->player->getColliderWeapon()->GetRight(),
            this->projectileSpeed,
            this->range,
            this->damage * GM->player->getDamage(),
            this->penetration
        );

        //벡터에 탄 push
        GM->player->getProjectiles().emplace_back(energeball);

        // 공속계산
        this->lastShotTime = currentTime;
        this->timeSinceLastTime = 1.0f / (this->attackSpeed * GM->player->getAttSpeed());
    }

    return false;
}