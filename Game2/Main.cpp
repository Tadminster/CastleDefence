#include "stdafx.h"
#include "Map.h"
#include "Player.h"
#include "Main.h"


Main::Main()
{
	mapManager = new Map();
	player = new Player();
}

Main::~Main()
{
	mapManager->~Map();
	player->~Player();
}

void Main::Init()
{
	mapManager->Init();
	player->Init();
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

		if (INPUT->KeyPress('W')) CAM->position.y += 5000 * DELTA;
		if (INPUT->KeyPress('S')) CAM->position.y -= 5000 * DELTA;
		if (INPUT->KeyPress('A')) CAM->position.x -= 5000 * DELTA;
		if (INPUT->KeyPress('D')) CAM->position.x += 5000 * DELTA;
	}
	//else
	
		CAM->position = player->getPos();

	mapManager->Relocation(player);
	mapManager->Update();
	player->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
	mapManager->Render();
	player->Render();
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