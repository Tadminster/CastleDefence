#include "stdafx.h"
#include "Player.h"
#include "MonsterManager.h"
#include "GameManager.h"

GameManager::~GameManager()
{
	player->~Player();
	monster->~MonsterManager();

	delete player;
	delete monster;
}

void GameManager::Init()
{
	player = new Player();
	monster = new MonsterManager();
}

void GameManager::Update()
{
	if (player->exp >= nextExp[player->level])
	{
		player->exp = 0;
		player->level++;

	}

}

