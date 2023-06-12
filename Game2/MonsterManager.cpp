#include "stdafx.h"
#include "Monster.h"
#include "MonsterManager.h"



void MonsterManager::Init()
{
}

void MonsterManager::Release()
{
}

void MonsterManager::Update()
{
	for (auto& enemy : this->enemy)
		enemy->Update();
}

void MonsterManager::LateUpdate()
{
}

void MonsterManager::Render()
{
	for (auto& enemy : this->enemy)
		enemy->Render();
}

void MonsterManager::AddEnemy(class Monster* monster)
{
	this->enemy.emplace_back(monster);
}