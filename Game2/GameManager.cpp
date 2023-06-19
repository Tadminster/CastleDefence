#include "stdafx.h"
#include "Player.h"
#include "MonsterManager.h"
#include "LevelUp.h"
#include "GameManager.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
	//lvUp->~LvUp();
	//player->~Player();
	//monster->~MonsterManager();

	delete levelUp;
	delete player;
	delete monster;
}

void GameManager::Init()
{
	player = new Player();
	monster = new MonsterManager();
	levelUp = new LevelUp();
}

void GameManager::Update()
{
	if (player->exp >= nextExp[player->level])
	{
		player->exp = 0;
		player->level++;
		lvUp = true;
	}

	if (lvUp)
	{
		levelUp->Update();
		if (levelUp->onClick() != 0)
		{
			lvUp = false;
		}
	}
}

void GameManager::Render()
{
	if (lvUp)
	{
		cout << "RENDER!" << endl;
		levelUp->Render();
	}
}
