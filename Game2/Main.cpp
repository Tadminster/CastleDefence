#include "stdafx.h"
#include "FileLoader.h"
#include "Main.h"


Main::Main()
{
	loadManager = new FileLoader();
}

Main::~Main()
{
}

void Main::Init()
{
	
}

void Main::Release()
{
}

void Main::Update()
{

	{	// DEBUG TEXT OUTPUT
		if (DEBUG_MODE)
		{
			ImGui::Text(u8"[ 마우스_X ] %f\n", INPUT->GetWorldMousePos().x);
			ImGui::Text(u8"[ 마우스_Y ] %f\n", INPUT->GetWorldMousePos().y);
			ImGui::Text("\n");
		}
	}

	loadManager->loadGame("map_1.map");
}

void Main::LateUpdate()
{
}

void Main::Render()
{
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