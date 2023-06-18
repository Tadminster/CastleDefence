#pragma once
#include "Monster.h"

class MegaSlime : public Monster
{
public:
	MegaSlime();
	~MegaSlime();

	void Init();
	void Update();
	void Render();
};

