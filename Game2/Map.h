#pragma once
class Map
{
private:
	class MapLoader*	mapLoader;
	ObRect*				col_background[4];
	ObImage*			img_background[4];

	//vector<ObImage*>	tilemap[10];

public:
	Map();
	~Map();

	void Init();
	void Update();
	void LateUpdate();
	void Render();
	void Relocation();
};

