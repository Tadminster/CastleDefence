#include "stdafx.h"
#include "MapLoader.h"
#include "Map.h"

Map::Map()
{
	mapLoader = new MapLoader();


	for (int i = 0; i < 4; i++)
	{
		col_background[i] = new ObRect();
		std::string imgFileName = "bg_" + to_string(i+1) + ".bmp";
		img_background[i] = new ObImage(std::wstring(imgFileName.begin(), imgFileName.end()).c_str());
		img_background[i]->SetParentRT(*col_background[i]);
	}
}

Map::~Map()
{
	delete mapLoader;
	for (int i = 0; i < 4; i++)
	{
		delete col_background[i];
		delete img_background[i];
	}
}

void Map::Init()
{
	//mapLoader->loadGame("TileMap.map", &this->tilemap);

	// 배경
	for (int i = 0; i < 4; i++)
	{
		Vector2 sacle(2300.f, 2300.f);
		col_background[i]->scale = sacle;
		col_background[i]->color = Vector4(1, 0.0, 0.0, 0.5);
		col_background[i]->isFilled = false;
		switch (i)
		{
			case 0 : col_background[i]->SetWorldPos(Vector2(sacle.x / 2, sacle.y / 2)); break;
			case 1 : col_background[i]->SetWorldPos(Vector2(sacle.x / 2, -sacle.y / 2)); break;
			case 2 : col_background[i]->SetWorldPos(Vector2(-sacle.x / 2, sacle.y / 2)); break;
			case 3 : col_background[i]->SetWorldPos(Vector2(-sacle.x / 2, -sacle.y / 2)); break;
		}
		img_background[i]->scale = sacle;
	}
}

void Map::Update()
{
	//for (int i = 0; i < 10; i++)
	//	ImGui::Text("vector[%d] size = %d", i, tilemap[i].size());

	//for (auto& tilemap_layer : this->tilemap)
	//	for (auto& tilemap_element : tilemap_layer)
	//		tilemap_element->Update();

	for (auto& col_bg : col_background)
		col_bg->Update();
	for (auto& img_bg : img_background)
		img_bg->Update();
}

void Map::LateUpdate()
{

}

void Map::Render()
{
	//for (auto& tilemap_layer : this->tilemap)
	//	for (auto& tilemap_element : tilemap_layer)
	//		tilemap_element->Render();

	for (auto& col_bg : col_background)
		col_bg->Render();
	for (auto& img_bg : img_background)
		img_bg->Render();
}

void Map::Relocation()
{
	for (auto& col_bg : col_background)
	{
		if (col_bg->Intersect(GM->player->getArea())) continue;

		float dirX = GM->player->getPos().x - col_bg->GetWorldPos().x;
		float dirY = GM->player->getPos().y - col_bg->GetWorldPos().y;

		float diffX = abs(GM->player->getPos().x - col_bg->GetWorldPos().x);
		float diffY = abs(GM->player->getPos().y - col_bg->GetWorldPos().y);

		dirX = dirX > 0 ? 1 : -1;
		dirY = dirY > 0 ? 1 : -1;

		if (diffX > diffY)
			col_bg->MoveWorldPos(RIGHT * dirX * col_bg->scale.x * 2);
		else if (diffX < diffY)
			col_bg->MoveWorldPos(UP * dirY * col_bg->scale.y * 2);
		else
		{
			col_bg->MoveWorldPos(RIGHT * dirX * col_bg->scale.x * 2);
			col_bg->MoveWorldPos(UP * dirY * col_bg->scale.y * 2);
		}
	}
}
