#include "stdafx.h"
#include "FileLoader.h"
#include <iostream>
#include <filesystem>
#include <fstream>

FileLoader::FileLoader() : savePath("../Save") {}
FileLoader::FileLoader(const std::string& savePath) : savePath(savePath) {}

bool FileLoader::loadGame(const std::string& fileName)
{
	// Path Init
	std::string filePath = this->savePath + "/" + fileName;
	std::ifstream mapFile(filePath, std::ios::binary);

	if (!mapFile.is_open())
	{
		std::cerr << "Error: 게임 불러오기 실패" << std::endl;
		return false;
	}

	while (true)
	{
		int srcRectX = 0, srcRectY = 0, layer = 0, colWidth = 0, colHeight = 0, tileWidth = 0, tileHeight = 0;
		Vector2 transform = Vector2(0, 0);
		Vector2 scale = Vector2(1, 1);
		Vector2 offset = Vector2(1, 1);
		std::string group = "", assetID = "";
		int numFrames = 0, frameSpeed = 0, frameOffset = 0;
		bool collider = false, animated = false, vertical = false, looped = false;

		// Read the contents of the file into the temporary variables
		mapFile >> group >> assetID >> tileWidth >> tileHeight >> srcRectX >> srcRectY >> layer >> transform.x >> transform.y >> scale.x >> scale.y >> collider;

		// If the tile is also a collider, load collider data
		//if (collider)
			//mapFile >> colWidth >> colHeight >> offset.x >> offset.y;

		//mapFile >> animated;

		//if (animated)
			//mapFile >> numFrames >> frameSpeed >> vertical >> looped >> frameOffset;

		// Check for end of file
		if (mapFile.eof())
			break;
	}

	// File Open
	//if (inFile.is_open())
	//{
	//	std::string loadedData;
	//	std::string imgFileName;

	//	for (int i = 0; i < 10; i++)
	//	{
	//		if (loadedData == "tiles" )
	//		{
	//			inFile >> loadedData;
	//			imgFileName = loadedData + ".png";
	//			ObImage* img = new ObImage(std::wstring(imgFileName.begin(), imgFileName.end()).c_str());
	//			
	//		}

	//	}

	mapFile.close();
	return true;
}
