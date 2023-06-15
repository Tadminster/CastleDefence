#include "stdafx.h"
#include "Map.h"
#include "MonsterManager.h"
#include "HUD.h"
#include "Main.h"


Main::Main()
{
	mapManager = new Map();
	hud = new HUD();
}

Main::~Main()
{
	mapManager->~Map();
	hud->~HUD();
}

void Main::Init()
{
	mapManager->Init();
	hud->Init();
	GM->Init();
	GM->player->Init();
	GM->monster->Init();
}

void Main::Release()
{
}

void Main::Update()
{
	GM->Update();
	// DEBUG TEXT OUTPUT
	if (DEBUG_MODE)
	{
		ImGui::Text(u8"[ 마우스_X ] %f\n", INPUT->GetWorldMousePos().x);
		ImGui::Text(u8"[ 마우스_Y ] %f\n", INPUT->GetWorldMousePos().y);
		ImGui::Text("\n");

		ImGui::Text(u8"[ 카메라_X ] %f\n", CAM->position.x);
		ImGui::Text(u8"[ 카메라_Y ] %f\n", CAM->position.y);
		ImGui::Text("\n");

		ImGui::Text(u8"[ 몬스터 ] %i\n", GM->monster->getEnemyCount());
		ImGui::Text(u8"[ 킬  수 ] %i\n", GM->kill);
		ImGui::Text("\n");

		ImGui::Text(u8"[ 경험치 ] %i / %i \n", GM->player->exp, GM->nextExp[GM->player->level]);
		ImGui::Text(u8"[ 레  벨 ] %i\n", GM->player->level);
		ImGui::Text("\n");

		if (INPUT->KeyPress(VK_UP)) CAM->position.y += 5000 * DELTA;
		if (INPUT->KeyPress(VK_DOWN)) CAM->position.y -= 5000 * DELTA;
		if (INPUT->KeyPress(VK_LEFT)) CAM->position.x -= 5000 * DELTA;
		if (INPUT->KeyPress(VK_RIGHT)) CAM->position.x += 5000 * DELTA;
	}
	
	CAM->position = GM->player->getPos();

	mapManager->Relocation();
	mapManager->Update();
	hud->Update();
	GM->player->Update();
	GM->monster->Update();
}

void Main::LateUpdate()
{
	GM->monster->LateUpdate();
}

void Main::Render()
{
	mapManager->Render();
	GM->player->Render();
	GM->monster->Render();
	hud->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"baram");
	app.SetInstance(instance);
	app.InitWidthHeight(1000.f, 1000.f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}