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
    dir(dir),
    speed(speed),
    range(range),
    damage(damage),
    traveledDistance(0.f)
{
    this->SetWorldPos(spawnPos);
    this->scale.x = 5;
    this->scale.y = 5;
    this->isFilled = false;
}

Projectile::~Projectile()
{
    //if (skin != nullptr)
        //delete skin;
}

void Projectile::Update()
{
    // 충돌 처리




    // 발사체 이동
    Vector2 velocity = (this->dir * this->speed);
    this->MoveWorldPos(velocity * DELTA);

    ObRect::Update();
    skin->Update();
    ImGui::Text("this.x = %f\n", this->GetWorldPos().x);
    ImGui::Text("this.y = %f\n", this->GetWorldPos().y);
    ImGui::Text("skin.x = %f\n", skin->GetWorldPos().x);
    ImGui::Text("skin.y = %f\n", skin->GetWorldPos().y);

    // 이동한 거리 계산
    traveledDistance += std::sqrt(std::pow(speed * DELTA, 2) + std::pow(speed * DELTA, 2));
}

void Projectile::Render()
{
    ObRect::Render();
    skin->Render();
}

bool Projectile::hasCollideWithMonster()
{
    for (auto& enemy : GM->monster->getEnemy())
    {
        if (enemy->getCollider()->Intersect(this))
        {
            cout << "collide" << endl;
            enemy->SetHP(-this->damage);
            return true;
        }
    }

    return false;
}
