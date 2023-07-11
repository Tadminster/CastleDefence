#include "stdafx.h"
#include "Map.h"
#include "HUD.h"
#include "Scene_2_inGame.h"

Scene_2_inGame::Scene_2_inGame()
{
	mapManager = new Map();

	GM->Init();
	hud = new HUD();
}

Scene_2_inGame::~Scene_2_inGame()
{
	mapManager->~Map();
}

void Scene_2_inGame::Init()
{
	mapManager->Init();

	GM->levelUp->Init();
	GM->player->Init();
	GM->monster->Init();
	GM->hud->Init();
}

void Scene_2_inGame::Release()
{
}

void Scene_2_inGame::Update()
{
	CAM->position = GM->player->getPos();

	// DEBUG TEXT OUTPUT
	if (GM->DEBUG_MODE)
	{
		ImGui::Text(u8"[ 마우스_X ] %f\n", INPUT->GetWorldMousePos().x);
		ImGui::Text(u8"[ 마우스_Y ] %f\n", INPUT->GetWorldMousePos().y);
		ImGui::Text("\n");

		ImGui::Text(u8"[ 카메라_X ] %f\n", CAM->position.x);
		ImGui::Text(u8"[ 카메라_Y ] %f\n", CAM->position.y);
		ImGui::Text("\n");

		ImGui::Text(u8"[ 몬스터 ] %i\n", GM->monster->getEnemyCount());

		ImGui::Text(u8"[ HP ] %f / %f \n", GM->player->getHp(), GM->player->getMaxHp());
		ImGui::Text(u8"[ ATT_POWER  ] %f \n", GM->player->damage);
		ImGui::Text(u8"[ ATT_SPEED  ] %f \n", GM->player->attackSpeed);
		ImGui::Text(u8"[ MOVE_SPEED ] %f \n", GM->player->moveSpeed);
		ImGui::Text("\n");

		if (INPUT->KeyPress(VK_UP)) CAM->position.y += 5000 * DELTA;
		if (INPUT->KeyPress(VK_DOWN)) CAM->position.y -= 5000 * DELTA;
		if (INPUT->KeyPress(VK_LEFT)) CAM->position.x -= 5000 * DELTA;
		if (INPUT->KeyPress(VK_RIGHT)) CAM->position.x += 5000 * DELTA;
	}

	static bool ending = true;
	if (GM->player->getPlayerAction() == PLAYER_ACTION::DEATH && ending)
	{
		ending = false;
		SCENE->ChangeScene("sc3", 2.0f);
		fadeout = 2.0f;
	}

	if (fadeout > 0.0f)
	{
		fadeout -= DELTA;
		LIGHT->lightColor.x = fadeout / 2.0f;
		LIGHT->lightColor.y = fadeout / 2.0f;
		LIGHT->lightColor.z = fadeout / 2.0f;
	}

	GM->Update();
	GM->hud->Update();
	GM->player->Update();
	GM->monster->Update();
	mapManager->Update();
}

void Scene_2_inGame::LateUpdate()
{
	mapManager->Relocation();
	GM->monster->LateUpdate();
}

void Scene_2_inGame::Render()
{
	mapManager->Render();
	GM->player->Render();
	GM->monster->Render();
	GM->hud->Render();
	GM->Render();
}

void Scene_2_inGame::ResizeScreen()
{
}
