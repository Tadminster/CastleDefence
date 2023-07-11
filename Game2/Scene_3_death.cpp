#include "stdafx.h"
#include "Scene_3_death.h"

Scene_3_death::Scene_3_death()
{
	bg_death = new ObImage(L"Title.png");
	//skin_btnConfirm = new ObImage(L"Title.png");
	btnConfirm = new ObRect();
}

Scene_3_death::~Scene_3_death()
{
	delete bg_death;
	//delete skin_btnConfirm;
	delete btnConfirm;

	TEXTURE->DeleteTexture(L"Title.png");
	//TEXTURE->DeleteTexture(L"Title.png");
}

void Scene_3_death::Init()
{
	LIGHT->lightColor.x = 0.5f;
	LIGHT->lightColor.y = 0.5f;
	LIGHT->lightColor.z = 0.5f;

	CAM->position = Vector2();

	bg_death->SetLocalPos(Vector2());
	bg_death->scale.x = app.GetWidth();
	bg_death->scale.y = app.GetHeight();

	btnConfirm->SetParentRT(*bg_death);
	btnConfirm->scale.x = 200;
	btnConfirm->scale.y = 100;
	btnConfirm->isFilled = false;
	btnConfirm->color = Vector4(0.5, 0.5, 0.5, 0.5);

	//skin_btnConfirm->SetParentRT(*btnConfirm);
	//skin_btnConfirm->scale = btnConfirm->scale;
}

void Scene_3_death::Release()
{
}

void Scene_3_death::Update()
{
	OnClick();

	bg_death->Update();
	btnConfirm->Update();
	//skin_btnConfirm->Update();

}

void Scene_3_death::LateUpdate()
{
	if (btnConfirm->IntersectScreenMouse(INPUT->GetScreenMousePos()))
	{
		btnConfirm->color = Vector4(1, 0, 0, 0.5);
	}
	else btnConfirm->color = Vector4(0.5, 0.5, 0.5, 0.5);
}

void Scene_3_death::Render()
{
	bg_death->Render();
	btnConfirm->Render();
	//skin_btnConfirm->Render();
}

void Scene_3_death::ResizeScreen()
{
}

void Scene_3_death::OnClick()
{
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		if (btnConfirm->IntersectScreenMouse(INPUT->GetScreenMousePos()))
		{
			SCENE->ChangeScene("sc1");
		}
	}
}