#include "stdafx.h"
#include "MapLoader.h"
#include "Map.h"

Map::Map()
{
	mapLoader = new MapLoader();
}

Map::~Map()
{
}

void Map::Init()
{
	mapLoader->loadGame("TileMap.map", &this->tilemap);
}

void Map::Update()
{
	for (int i = 0; i < 10; i++)
		ImGui::Text("vector[%d] size = %d", i, tilemap[i].size());

	for (auto& tilemap_layer : this->tilemap)
		for (auto& tilemap_element : tilemap_layer)
			tilemap_element->Update();
}

void Map::LateUpdate()
{

}

void Map::Render()
{
	for (auto& tilemap_layer : this->tilemap)
		for (auto& tilemap_element : tilemap_layer)
			tilemap_element->Render();
}