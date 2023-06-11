#pragma once
class MapLoader
{
private:
	class FilePath* imgPath;
	std::string savePath;

public:
	MapLoader();
	MapLoader(const std::string& savePath);

	bool loadGame(const std::string& fileName, vector<ObImage*> (*tilemapPtr)[10]);
};
