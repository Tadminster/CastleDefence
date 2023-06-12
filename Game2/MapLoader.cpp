#include "stdafx.h"
#include "FilePath.h"
#include "MapLoader.h"

#include <iostream>
#include <filesystem>
#include <fstream>

MapLoader::MapLoader() : savePath("../Contents/Save"), imgPath(new FilePath()) {}
MapLoader::MapLoader(const std::string& savePath) : savePath(savePath), imgPath(new FilePath()) {}

bool MapLoader::loadGame(const std::string& saveFile, vector<ObImage*> (*tilemapPtr)[10])
{
	// 경로 설정
	std::string filePath = this->savePath + "/" + saveFile;
	std::ifstream mapFile(filePath, std::ios::binary);

	// 파일 오픈 실패시 return
	if (!mapFile.is_open())
	{
		std::cerr << "Error: 게임 불러오기 실패" << std::endl;
		return false;
	}

	while (true)
	{
		int		tileWidth	= 0;
		int		tileHeight	= 0;
		float	uvX			= 0;
		float	uvY			= 0;
		float	uvZ			= 0;
		float	uvW			= 0;
		int		layer		= 0;
		int		colWidth	= 0;
		int		colHeight	= 0;
		int		numFrames	= 0;
		int		frameSpeed	= 0;
		int		frameOffset = 0;

		Vector2 transform	= Vector2(0, 0);
		Vector2	scale		= Vector2(1, 1);
		Vector2 offset		= Vector2(1, 1);

		bool	collider	= false;
		bool	animated	= false;
		bool	vertical	= false;
		bool	looped		= false;

		std::string group = "";
		std::string assetID = "";
		std::string imgFileName = "";

		mapFile >> group;
		if (group == "tiles")
		{
			// 데이터를 임시 변수에 저장
			mapFile
				>> assetID
				>> tileWidth >> tileHeight >> uvX >> uvY >> layer
				>> transform.x >> transform.y >> scale.x >> scale.y;

			mapFile >> collider;
			if (collider)
				mapFile >> colWidth >> colHeight >> offset.x >> offset.y;

			mapFile >> animated;
			if (animated)
				mapFile >> numFrames >> frameSpeed >> vertical >> looped >> frameOffset;

			// 이미지 생성
			//imgFileName = assetID + ".png";
			imgFileName = imgPath->getPath(assetID);
			ObImage* img = new ObImage(std::wstring(imgFileName.begin(), imgFileName.end()).c_str());

			// 이미지 Initialize
			img->uv.x = static_cast<float>(uvX) / img->imageSize.x;
			img->uv.y = static_cast<float>(uvY) / img->imageSize.y;
			img->uv.z = static_cast<float>(uvX + tileWidth) / img->imageSize.x;
			img->uv.w = static_cast<float>(uvY + tileHeight) / img->imageSize.y;
			img->scale.x = scale.x * 16;
			img->scale.y = scale.y * 16;
			img->pivot = OFFSET_LT;
			img->SetWorldPos(Vector2(transform.x, -transform.y));

			// 이미지 vector에 push
			(*tilemapPtr)[layer].emplace_back(img);
		}

		// 모든 데이터를 다 읽었는지 확인
		if (mapFile.eof())
			break;
	}

	// 파일 닫고, retrun ture
	mapFile.close();
	return true;
}
