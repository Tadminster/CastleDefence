#include <map>
#include <string>
#include <stdexcept>
#include <iostream>

#include "FilePath.h"

FilePath::FilePath()
{
    this->path.insert(std::make_pair("Grass", ".\\MiniWorldSprites\\Ground\\Grass.png"));
    this->path.insert(std::make_pair("Grass2", ".\\MiniWorldSprites\\Ground\\Grass2.png"));
    this->path.insert(std::make_pair("Cliff", ".\\MiniWorldSprites\\Ground\\Cliff.png"));
    this->path.insert(std::make_pair("TexturedGrass", ".\\MiniWorldSprites\\Ground\\TexturedGrass.png"));

    this->path.insert(std::make_pair("Trees", ".\\MiniWorldSprites\\Nature\\Trees.png"));
    this->path.insert(std::make_pair("Wheatfield", ".\\MiniWorldSprites\\Nature\\Wheatfield.png"));

    this->path.insert(std::make_pair("RedKeep", ".\\MiniWorldSprites\\Buildings\\Red\\RedKeep.png"));
    this->path.insert(std::make_pair("Houses", ".\\MiniWorldSprites\\Buildings\\Wood\\Houses.png"));
    this->path.insert(std::make_pair("Tower", ".\\MiniWorldSprites\\Buildings\\Wood\\Tower.png"));
    this->path.insert(std::make_pair("Tower2", ".\\MiniWorldSprites\\Buildings\\Wood\\Tower2.png"));
    this->path.insert(std::make_pair("Taverns", ".\\MiniWorldSprites\\Buildings\\Wood\\Taverns.png"));
    this->path.insert(std::make_pair("Barracks", ".\\MiniWorldSprites\\Buildings\\Wood\\Barracks.png"));
    this->path.insert(std::make_pair("LimeTower", ".\\MiniWorldSprites\\Buildings\\Lime\\LimeTower.png"));

    this->path.insert(std::make_pair("Bridge", ".\\MiniWorldSprites\\Miscellaneous\\Bridge.png"));
    this->path.insert(std::make_pair("QuestBoard", ".\\MiniWorldSprites\\Miscellaneous\\QuestBoard.png"));
    this->path.insert(std::make_pair("StreetSigns", ".\\MiniWorldSprites\\Miscellaneous\\StreetSigns.png"));
}

std::string FilePath::getPath(std::string& key)
{
    try 
    {
        std::string value = path.at(key);
        return value;
    }
    catch (const std::out_of_range& e) 
    {
        std::cout
            << "PATH ERROR, KEY =" + key << std::endl
            << "해당 키가 존재하지 않습니다." << std::endl
            << "KEY와 PATH를 다시 확인하십시오" << std::endl;
    }
}
