#include "stdafx.h"
#include "Floor.h"

Floor::Floor(int numberMidtiles)
{
	this->tileInterval = 100;

	// 미드
	this->midtiles = numberMidtiles;
	if (midtiles > 0)
	{
		mid = new ObRect* [midtiles];
		mid_image = new ObImage* [midtiles];
		for (int i = 0; i < midtiles; i++)
		{
			mid[i] = new ObRect();
			mid[i]->pivot = OFFSET_LT;
			mid[i]->color = Color(1.0f, 1.0f, 1.0f, 1.0f);

			mid_image[i] = new ObImage(L"floor.png");
			mid_image[i]->SetParentRT(*mid[i]);
			mid_image[i]->pivot = OFFSET_LT;
			mid_image[i]->color = Color(0.6f, 0.6f, 0.6f, 0.5f);
		}
	}

	// 사이드
	for (int i = 0; i < 2; i++)
	{
		side_TOP[i] = new ObRect;
		side_LR[i] = new ObRect;
		side_image[i] = new ObImage(L"floor.png");
		
		side_LR[i]->SetParentRT(*side_TOP[i]);
		side_image[i]->SetParentRT(*side_TOP[i]);

		side_TOP[i]->pivot = OFFSET_LT;
		side_LR[i]->pivot = OFFSET_LT;
		side_image[i]->pivot = OFFSET_LT;
		
		side_TOP[i]->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
		side_LR[i]->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
		side_image[i]->color = Color(0.6f, 0.6f, 0.6f, 0.5f);
	}
}

Floor::~Floor()
{
	if (midtiles > 0)
	{
		for (int i = 0; i < midtiles; i++)
		{
			delete[] mid[i];
			delete[] mid_image[i];
			TEXTURE->DeleteTexture(L"floor.png");
		}
	}
	delete mid;
	delete mid_image;

	for (int i = 0; i < 2; i++)
	{
		delete[] side_TOP[i];
		delete[] side_LR[i];
	}
}

void Floor::Init(float pos_x)
{
	int interval_weight = 0;
	// 16 32 48
	// 48 96 144

	side_TOP[0]->scale.x = 100.f;
	side_TOP[0]->scale.y = 5.0f;
	side_TOP[0]->SetWorldPos(Vector2(pos_x, -160));

	side_LR[0]->scale.x = 5.0f;
	side_LR[0]->scale.y = 160.f;
	side_LR[0]->SetLocalPosY(-3);
	//side_LR[0]->SetWorldPos(Vector2(pos_x, -160));

	side_image[0]->scale.x = side_TOP[0]->scale.x;
	side_image[0]->scale.y = side_LR[0]->scale.y;
	side_image[0]->uv.x = 4.0f / side_image[0]->imageSize.x;
	side_image[0]->uv.y = 8.0f / side_image[0]->imageSize.y;
	side_image[0]->uv.z = 19.0f / side_image[0]->imageSize.x;
	side_image[0]->uv.w = 55.0f / side_image[0]->imageSize.y;
	interval_weight += tileInterval;

	if (midtiles > 0)
	{
		for (int i = 0; i < midtiles; i++)
		{
			mid[i]->scale.x = 100.f;
			mid[i]->scale.y = 5.0f;
			mid[i]->SetWorldPos(Vector2(pos_x + interval_weight, -160));

			mid_image[i]->scale.x = mid[i]->scale.x;
			mid_image[i]->scale.y = side_LR[0]->scale.y;
			mid_image[i]->uv.x = 24.0f / mid_image[i]->imageSize.x;
			mid_image[i]->uv.y = 8.0f / mid_image[i]->imageSize.y;
			mid_image[i]->uv.z = 39.0f / mid_image[i]->imageSize.x;
			mid_image[i]->uv.w = 55.0f / mid_image[i]->imageSize.y;
			interval_weight += tileInterval;
		}
	}

	side_TOP[1]->scale.x = 100.0f;
	side_TOP[1]->scale.y = 5.0f;
	side_TOP[1]->SetWorldPos(Vector2(pos_x + interval_weight, -160));
	interval_weight += tileInterval;

	side_LR[1]->scale.x = 5.0f;
	side_LR[1]->scale.y = 160.f;
	side_LR[1]->SetLocalPosX(tileInterval);
	side_LR[1]->SetLocalPosY(-5);

	side_image[1]->scale.x = side_TOP[1]->scale.x;
	side_image[1]->scale.y = side_LR[1]->scale.y;
	side_image[1]->uv.x = 44.0f / side_image[1]->imageSize.x;
	side_image[1]->uv.y = 8.0f / side_image[1]->imageSize.y;
	side_image[1]->uv.z = 59.0f / side_image[1]->imageSize.x;
	side_image[1]->uv.w = 55.0f / side_image[1]->imageSize.y;
}

void Floor::Update()
{
	for (int i = 0; i < 2; i++)
	{
		side_TOP[i]->Update();
		side_LR[i]->Update();
		side_image[i]->Update();
	}

	if (midtiles > 0)
		for (int i = 0; i < midtiles; i++)
		{
			mid[i]->Update();
			mid_image[i]->Update();
		}
}


void Floor::Render()
{
	if (DEBUG_MODE)
	{
		for (int i = 0; i < 2; i++)
		{
			side_TOP[i]->Render();
			side_LR[i]->Render();
		}

		if (midtiles > 0)
			for (int i = 0; i < midtiles; i++)
			{
				mid[i]->Render();
			}
	}
	else
	{
		for (int i = 0; i < 2; i++)
			side_image[i]->Render();

		if (midtiles > 0)
			for (int i = 0; i < midtiles; i++)
				mid_image[i]->Render();
	}
}

void Floor::PushVector(vector<ObRect*>& floors, vector<ObRect*>& obstacles)
{
	// 바닥
	if (midtiles > 0)
		for (int i = 0; i < midtiles; i++)
			floors.emplace_back(mid[i]);

	for (int i = 0; i < 2; i++)
	{
		// 바닥
		floors.emplace_back(side_TOP[i]);
		// 옆면
		obstacles.emplace_back(side_LR[i]);
	}
}
