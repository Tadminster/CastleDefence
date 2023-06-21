#include "stdafx.h"
#include "PlayerTrail.h"

PlayerTrail::PlayerTrail()
{
    trailTimer = 0.05f;
    trialTime = 0.0f;

    playerTrail.resize(3);
    //for (int i = 0; i < 30; i++)
    for (auto it = playerTrail.begin(); it != playerTrail.end(); it++)
    {
        (*it) = new ObImage(L"player_run_left.png");
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
        (*it)->scale = GM->player->getSkinScale()->scale;
        (*it)->maxFrame.x = GM->player->getSkinScale()->maxFrame.x;
        (*it)->maxFrame.y = GM->player->getSkinScale()->maxFrame.y;
        (*it)->color.w = 0.3;
    }
}

//void PlayerTrail::Release()
//{
//}

void PlayerTrail::Update()
{
    if (TIMER->GetTick(trialTime, trailTimer))
    {
        for (auto it = playerTrail.begin(); it != playerTrail.end(); it++)
        {
            (*it)->color.w -= 0.1f;
        }

        playerTrail.front()->SetWorldPos(GM->player->getCollider()->GetWorldPos());
        playerTrail.front()->frame.x = GM->player->getSkinScale()->frame.x;
        playerTrail.front()->frame.y = GM->player->getSkinScale()->frame.y;
        playerTrail.front()->color.w = 0.3f;

        //playerTrail.front()->rotation = player->rotation;
        playerTrail.push_back(playerTrail.front());
        playerTrail.pop_front();
    }


    for (auto it = playerTrail.begin(); it != playerTrail.end(); it++)
    {
        (*it)->Update();
    }
}

//void PlayerTrail::LateUpdate()
//{
//}

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
        (*it) = new ObImage(L"player_run_left.png");
        (*it)->scale.x = 100.0f;
        (*it)->scale.y = 100.0f;
    }
}
