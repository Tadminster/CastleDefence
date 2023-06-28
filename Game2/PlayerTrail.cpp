#include "stdafx.h"
#include "PlayerTrail.h"

PlayerTrail::PlayerTrail()
{
    trailTimer = 0.05f;
    trialTime = 0.0f;

    playerTrail.resize(3);
    for (auto it = playerTrail.begin(); it != playerTrail.end(); it++)
    {
        (*it) = new ObImage(L"player_roll.png");
    }
}

PlayerTrail::~PlayerTrail()
{
    for (auto it = playerTrail.begin(); it != playerTrail.end(); it++)
    {
        delete (*it);
    }
}

void PlayerTrail::Init()
{
    for (auto it = playerTrail.begin(); it != playerTrail.end(); it++)
    {
        (*it)->pivot = OFFSET_B;
        (*it)->scale = GM->player->getSkinRoll()->scale;
        (*it)->maxFrame.x = GM->player->getSkinRoll()->maxFrame.x;
        (*it)->maxFrame.y = GM->player->getSkinRoll()->maxFrame.y;
        (*it)->color.w = 0.3;
    }
}

void PlayerTrail::Update()
{
    if (TIMER->GetTick(trialTime, trailTimer))
    {
        for (auto it = playerTrail.begin(); it != playerTrail.end(); it++)
        {
            (*it)->color.w -= 0.1f;
        }

        playerTrail.front()->SetWorldPos(GM->player->getCollider()->GetWorldPos());
        playerTrail.front()->frame.x = GM->player->getSkinRoll()->frame.x;
        playerTrail.front()->frame.y = GM->player->getSkinRoll()->frame.y;
        playerTrail.front()->color.w = 0.3f;

        playerTrail.push_back(playerTrail.front());
        playerTrail.pop_front();
    }

    for (auto it = playerTrail.begin(); it != playerTrail.end(); it++)
    {
        (*it)->Update();
    }
}

void PlayerTrail::Render()
{
    for (auto it = playerTrail.begin(); it != playerTrail.end(); it++)
    {
        (*it)->Render();
    }
}

void PlayerTrail::Resize(int value)
{
    // 기존 잔상을 다 지우고
    for (auto it = playerTrail.begin(); it != playerTrail.end(); it++)
    {
        delete (*it);
    }

    // 새로운 사이즈와 객체 할당
    playerTrail.resize(value);
    for (auto it = playerTrail.begin(); it != playerTrail.end(); it++)
    {
        (*it) = new ObImage(L"player_roll.png");
        (*it)->pivot = OFFSET_B;
        (*it)->scale = GM->player->getSkinRoll()->scale;
        (*it)->maxFrame.x = GM->player->getSkinRoll()->maxFrame.x;
        (*it)->maxFrame.y = GM->player->getSkinRoll()->maxFrame.y;
        (*it)->color.w = 0.3;
    }
}
