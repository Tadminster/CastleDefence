#include "stdafx.h"
#include "Scene_1_title.h"

Scene_1_title::Scene_1_title()
{
	bg_title = new ObImage(L"Title.png");
	//skin_btnStart = new ObImage(L"Scene_1_title.png");
	//skin_btnExit = new ObImage(L"Scene_1_title.png");
	btnStart = new ObRect();
	btnExit = new ObRect();
}

Scene_1_title::~Scene_1_title()
{
	delete bg_title;
	delete btnStart;
	delete btnExit;

	TEXTURE->DeleteTexture(L"Title.png");
}


void Scene_1_title::Init()
{
	bg_title->SetWorldPos(Vector2());
	//bg_title->scale.x = bg_title->imageSize.x;
	//bg_title->scale.y = bg_title->imageSize.y;
	bg_title->scale.x = app.GetWidth();
	bg_title->scale.y = app.GetHeight();

	btnStart->SetParentRT(*bg_title);
	btnStart->SetLocalPosY(0);
	btnStart->scale.x = 300;
	btnStart->scale.y = 150;
	btnStart->isFilled = false;
	btnStart->color = Vector4(0.5, 0.5, 0.5, 0.5);

	btnExit->SetParentRT(*bg_title);
	btnExit->SetLocalPosY(-200);
	btnExit->scale.x = 300;
	btnExit->scale.y = 150;
	btnExit->isFilled = false;
	btnExit->color = Vector4(0.5, 0.5, 0.5, 0.5);
}

void Scene_1_title::Release()
{
}

void Scene_1_title::Update()
{
	OnClick();

	bg_title->Update();
	btnStart->Update();
	btnExit->Update();
}

void Scene_1_title::LateUpdate()
{
	//if (btnStart->Intersect(INPUT->GetWorldMousePos()))
	//{
	//	cout << " 마우스 올라감" << endl;
	//	btnStart->color = Vector4(1, 0, 0, 0.5);
	//} 

	if (btnStart->IntersectScreenMouse(INPUT->GetScreenMousePos()))
	{
		btnStart->color = Vector4(1, 0, 0, 0.5);
	}
	else btnStart->color = Vector4(0.5, 0.5, 0.5, 0.5);

	if (btnExit->IntersectScreenMouse(INPUT->GetScreenMousePos()))
	{
		btnExit->color = Vector4(1, 0, 0, 0.5);
	}
	else btnExit->color = Vector4(0.5, 0.5, 0.5, 0.5);
}

void Scene_1_title::Render()
{
	bg_title->Render();
	btnStart->Render();
	btnExit->Render();
}

void Scene_1_title::ResizeScreen()
{
}

void Scene_1_title::OnClick()
{
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		if (btnStart->IntersectScreenMouse(INPUT->GetScreenMousePos()))
		{
			SCENE->ChangeScene("sc2");
		}
		if (btnExit->IntersectScreenMouse(INPUT->GetScreenMousePos()))
		{
			exit(1);
		}
	}
}