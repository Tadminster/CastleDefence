#include "stdafx.h"
#include "Player.h"
#include "Main.h"
#include "Map.h"


Main::Main()
{
	map = new Map();
	player = new Player();

	gameStart = false;
	score_cur = 0;
	score_max = 0;
}

Main::~Main()
{
	player->~Player();
	map->~Map();
}
void Main::Init()
{
	
}

void Main::Release()
{
}

void Main::Update()
{
	score_cur = (player->getPos().x - 50) / 10;
	if (score_max < score_cur) score_max = score_cur;

	{	// DEBUG TEXT OUTPUT
		if (DEBUG_MODE)
		{
			ImGui::Text("[ MOUSE_X ] %f\n", INPUT->GetWorldMousePos().x);
			ImGui::Text("[ MOUSE_Y ] %f\n", INPUT->GetWorldMousePos().y);
			ImGui::Text("\n");

			ImGui::Text("[ PLAYER_X ] %f\n", player->getPos().x);
			ImGui::Text("[ PLAYER_Y ] %f\n", player->getPos().y);
			ImGui::Text("[ PLAYER_G ] %f\n", player->getGravity());
		}
		else
		{
			ImGui::Text("KEYS");
			ImGui::Text(u8"[ VK_RIGHT ] 게임 시작\n");
			ImGui::Text(u8"[  U  P  ] 점프 / 이단점프\n");
			//ImGui::Text("[ VK_RIGHT ] RIGHT MOVE \n");
			ImGui::Text("\n");

			ImGui::Text(u8"[ 현재 점수 ] %d\n", score_cur);
			ImGui::Text(u8"[ 최고 점수 ] %d\n", score_max);
		}
	}
	
	map->Update();
	map->collision(player);
	map->relocate(player->getPos());
	player->Update(map);
	CAM->position.x = player->getPos().x + 200;
}

void Main::LateUpdate()
{
	map->LateUpdate();
}

void Main::Render()
{
	map->Render(0);
	player->Render();
	map->Render(1);
	map->Render(2);
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(1000.0f, 640.0f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}