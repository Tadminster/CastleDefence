#pragma once
#include "Monster.h"

class KingSlime : public Monster
{
public:
	KingSlime();
	~KingSlime();

	void Init();
	void Update();
	void Render();
};

