#pragma once
#include "../2DFrameWork/framework.h"
#pragma comment (lib,"../Build/2DFrameWork/2DFrameWork.lib")

#include <sstream>

#include "GameManager.h"
#include "Title.h"
#include "LevelUp.h"
#include "MonsterManager.h"
#include "Player.h"
#include "Monster.h"

//Singleton Macro
#define GM		GameManager::GetInstance()