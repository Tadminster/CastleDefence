#include "stdafx.h"
#include "Player.h"
#include "GameManager.h"

GameManager::~GameManager()
{
	player->~Player();
	delete player;
}

void GameManager::Init()
{
	player = new Player();
}

void GameManager::Release()
{
}

void GameManager::Update()
{
}

void GameManager::LateUpdate()
{
}

void GameManager::Render()
{
}


