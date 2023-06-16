#pragma once
#include "Monster.h"

class KingMegaSlime : public Monster
{
public:
	KingMegaSlime();
	~KingMegaSlime();

	void Init();
	void Update();
	void Render();
};

