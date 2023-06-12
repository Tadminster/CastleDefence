#pragma once
#include "Monster.h"

class Slime : public Monster
{
public:
	Slime();
	~Slime();

	void Init();
	void Update();
	void Render();
};

