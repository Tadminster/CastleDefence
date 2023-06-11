#pragma once
class Map
{
private:
	class MapLoader* mapLoader;
	vector<ObImage*> tilemap[10];

public:
	Map();
	~Map();

	void Init();
	void Update();
	void LateUpdate();
	void Render();
};

