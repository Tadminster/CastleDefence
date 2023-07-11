#include "stdafx.h"
#include "Scene_1_title.h"
#include "Scene_2_inGame.h"
#include "Scene_3_death.h"
#include "Main.h"


Main::Main()
{ 
	sc_1_title = new Scene_1_title();
	sc_2_inGame = new Scene_2_inGame();
	sc_3_death = new Scene_3_death();
}

Main::~Main()
{
	SCENE->~SceneManager();
}

void Main::Init()
{
	sc_1_title->Init();
	sc_2_inGame->Init();
	sc_3_death->Init();
	SCENE->AddScene("sc1", sc_1_title);
	SCENE->AddScene("sc2", sc_2_inGame);
	SCENE->AddScene("sc3", sc_3_death);
	SCENE->ChangeScene("sc1");
}

void Main::Release()
{
	SCENE->Release();
}

void Main::Update()
{
	SCENE->Update();
}

void Main::LateUpdate()
{
	SCENE->LateUpdate();
}

void Main::Render()
{
	SCENE->Render();
}

void Main::ResizeScreen()
{
	SCENE->ResizeScreen();
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