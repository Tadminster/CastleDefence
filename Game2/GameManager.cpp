#include "stdafx.h"
#include "ItemList.h"
#include "Player.h"
#include "MonsterManager.h"
#include "LevelUp.h"
#include "GameManager.h"

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
	itemList = new ItemList();
	itemList->Init();
	player = new Player();
	monster = new MonsterManager();
	levelUp = new LevelUp();
}

void GameManager::Update()
{
	ImGui::Text("effects : %i\n", afterEffectManager.size());

	if (player->level == 0)
	{
		player->exp += 1;
	}

	// 레벨업하면
	if (player->exp >= nextExp[player->level])
	{
		// 경험치를 0으로 초기화
		player->exp = 0;
		// 레벨 1상승
		player->level++;
		// 레벨 이벤트 시작
		lvUp = true;
		// 게임을 멈춤
		app.deltaScale = 0;
		// 아이템 받아오기
		if (player->level == 1)
			levelUp->GetFirstItem();
		else
			levelUp->GetRandomItem();
	}

	if (lvUp)
	{
		// 시간을 멈추고
		TIMER->TimeStop();
		// 레벨업 클래스 업데이트
		levelUp->Update();

		// 버튼 클릭하면
		if (levelUp->onClick() != 0)
		{
			// 레벨 이벤트 종료
			lvUp = false;
			// 게임 다시 시작
			app.deltaScale = 1;
		}
	}

	// 수명이 다한 이펙트 삭제
	afterEffectManager.erase(
	std::remove_if
	(
		afterEffectManager.begin(),
		afterEffectManager.end(),
		[](unique_ptr<ObImage>& effect) { return effect->frame.x + 1 == effect->maxFrame.x; }
	),
	afterEffectManager.end()
	);

	for (auto& afterEffect : afterEffectManager)
		afterEffect->Update();
}

void GameManager::Render()
{
	for (auto& afterEffect : afterEffectManager)
		afterEffect->Render();

	if (lvUp)
	{
		levelUp->Render();
	}
}
