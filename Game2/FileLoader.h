#pragma once
class FileLoader
{
private:
	std::string savePath;

public:
	FileLoader();
	FileLoader(const std::string& savePath);

	bool loadGame(const std::string& fileName);
};
