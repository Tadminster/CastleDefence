#include <map>
#include <string>

#include "FilePath.h"

FilePath::FilePath()
{
    this->path.insert("Grass", "..\\\Content\\Images\\MiniWorldSprites\\Ground\\Grass.png");
    this->path.insert("RedKeep", "..\\\Content\\Images\\MiniWorldSprites\\Buildings\\Red\\RedKeep.png");
    this->path.insert("Houses", "..\\\Content\\Images\\MiniWorldSprites\\Buildings\\Wood\\Houses.png");
    this->path.insert("Tower", "..\\\Content\\Images\\MiniWorldSprites\\Buildings\\Wood\\Tower.png");
    this->path.insert("Taverns", "..\\\Content\\Images\\MiniWorldSprites\\Buildings\\Wood\\Taverns.png");
    this->path.insert("Trees", "..\\\Content\\Images\\MiniWorldSprites\\Nature\\Trees.png");
    this->path.insert("Barracks", "..\\\Content\\Images\\MiniWorldSprites\\Buildings\\Wood\\Barracks.png");
    this->path.insert("Wheatfield", "..\\\Content\\Images\\MiniWorldSprites\\Nature\\Wheatfield.png");
    this->path.insert("Bridge", "..\\\Content\\Images\\MiniWorldSprites\\Miscellaneous\\Bridge.png");
    this->path.insert("QuestBoard", "..\\\Content\\Images\\MiniWorldSprites\\Miscellaneous\\QuestBoard.png");
    this->path.insert("StreetSigns", "..\\\Content\\Images\\MiniWorldSprites\\Miscellaneous\\StreetSigns.png");
}
