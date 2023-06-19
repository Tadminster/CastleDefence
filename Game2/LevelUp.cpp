#include "stdafx.h"
#include "LevelUp.h"

LevelUp::LevelUp()
{
	for (int i = 0; i < 3; i++)
	{
		btn_col[i] = new ObRect();
		btn_skin[i] = new ObImage(L"Item_00.png");
		btn_skin[i]->SetParentRT(*btn_col[i]);
	}
}

LevelUp::~LevelUp()
{
	for (int i = 0; i < 3; i++)
	{
		delete[] btn_col[i];
		delete[] btn_skin[i];
	}
}

void LevelUp::Init()
{
	//Utility::WorldToScreen(Vector2(CAM->position.x - 200, 0)).x



	for (int i = 0; i < 3; i++)
	{
		btn_col[i]->isFilled = false;
		btn_col[i]->scale = Vector2(64, 64);

		//btn_skin[i]->space = SPACE::SCREEN;
		btn_skin[i]->scale = btn_col[i]->scale;
		//btn_skin[i]->imageSize.x = 50;
		//btn_skin[i]->imageSize.y = 50;
	}

	float PosY = Utility::WorldToScreen(Vector2(0, CAM->position.y)).y;


}

void LevelUp::Release()
{
}

void LevelUp::Update()
{
	for (int i = 0; i < 3; i++)
	{
		btn_col[0]->SetWorldPos(Vector2(CAM->position.x - 200, CAM->position.y));
		btn_col[1]->SetWorldPos(Vector2(CAM->position.x, CAM->position.y));
		btn_col[2]->SetWorldPos(Vector2(CAM->position.x + 200, CAM->position.y));
	}

	for (auto& col : btn_col)
		col->Update();
	for (auto& skin : btn_skin)
		skin->Update();
}

void LevelUp::LateUpdate()
{
}

void LevelUp::Render()
{
	for (auto& col : btn_col)
		col->Render();
	for (auto& skin : btn_skin)
		skin->Render();
}

int LevelUp::onClick()
{
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		if (btn_col[0]->Intersect(INPUT->GetWorldMousePos()))
		{
			return 1;
		}
		if (btn_col[1]->Intersect(INPUT->GetWorldMousePos()))
		{
			return 2;
		}
		if (btn_col[2]->Intersect(INPUT->GetWorldMousePos()))
		{
			return 3;
		}

		return 0;
	}
}