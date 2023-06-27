#pragma once
#include "Monster.h"

class SkeletonWarrior : public Monster
{
public:
	SkeletonWarrior();
	~SkeletonWarrior();

	void Init();
	void Update();
	void Render();
};



