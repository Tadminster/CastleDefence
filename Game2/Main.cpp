#include "stdafx.h"
#include "Map.h"
//#include "MonsterManager.h"
#include "HUD.h"
#include "Scene_1_title.h"
#include "Main.h"


Main::Main()
{ 
	sc_1_title = new Scene_1_title();

	GM->Init();
	mapManager = new Map();
	//hud = new HUD();
}

Main::~Main()
{
	mapManager->~Map();
}

void Main::Init()
{
	sc_1_title->Init();
	SCENE->Add
	GM->levelUp->Init();
	GM->player->Init();
	GM->monster->Init();
	GM->hud->Init();

	mapManager->Init();
}

void Main::Release()
{
}

void Main::Update()
{
	if (GM->isTitleEntering)
	{
		GM->title->Update();
	}
	else
	{

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

		CAM->position = GM->player->getPos();

		mapManager->Relocation();
		mapManager->Update();

		GM->Update();
		GM->hud->Update();
		GM->player->Update();
		GM->monster->Update();

		//if (GM->lvUp)
			//GM->levelUp->Update();
	}

}

void Main::LateUpdate()
{
	if (GM->isTitleEntering)
	{
		GM->title->LateUpdate();
	}
	else
	{
		GM->monster->LateUpdate();
	}

}

void Main::Render()
{
	if (GM->isTitleEntering)
	{
		GM->title->Render();
	}
	else
	{
		mapManager->Render();
		GM->player->Render();
		GM->monster->Render();
		GM->hud->Render();
		GM->Render();
	}

	//if (GM->lvUp)
		//GM->levelUp->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"VamsurLike");
	app.SetInstance(instance);
	app.InitWidthHeight(1440.f, 900.f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}