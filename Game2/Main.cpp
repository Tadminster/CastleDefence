﻿#include "stdafx.h"
#include "Map.h"
#include "MonsterManager.h"
#include "Slime.h"
#include "Main.h"


Main::Main()
{
	mapManager = new Map();
}

Main::~Main()
{
	mapManager->~Map();
}

void Main::Init()
{
	mapManager->Init();
	GM->Init();
	GM->player->Init();
	MONSTER->Init();
}

void Main::Release()
{
}

void Main::Update()
{
	// DEBUG TEXT OUTPUT
	if (DEBUG_MODE)
	{
		ImGui::Text(u8"[ 마우스_X ] %f\n", INPUT->GetWorldMousePos().x);
		ImGui::Text(u8"[ 마우스_Y ] %f\n", INPUT->GetWorldMousePos().y);
		ImGui::Text("\n");

		ImGui::Text(u8"[ 카메라_X ] %f\n", CAM->position.x);
		ImGui::Text(u8"[ 카메라_Y ] %f\n", CAM->position.y);
		ImGui::Text("\n");

		ImGui::Text(u8"[ 몬스터수 ] %i\n", MONSTER->getEnemyCount());
		ImGui::Text("\n");

		if (INPUT->KeyPress(VK_UP)) CAM->position.y += 5000 * DELTA;
		if (INPUT->KeyPress(VK_DOWN)) CAM->position.y -= 5000 * DELTA;
		if (INPUT->KeyPress(VK_LEFT)) CAM->position.x -= 5000 * DELTA;
		if (INPUT->KeyPress(VK_RIGHT)) CAM->position.x += 5000 * DELTA;
	}
	//else
	
	CAM->position = GM->player->getPos();

	mapManager->Relocation();
	mapManager->Update();
	MONSTER->Update();
	GM->player->Update();
}

void Main::LateUpdate()
{
	MONSTER->LateUpdate();
}

void Main::Render()
{
	mapManager->Render();
	MONSTER->Render();
	GM->player->Render();

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