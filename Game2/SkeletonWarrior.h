﻿#pragma once
#include "Monster.h"

class SkeletonWarrior : public Monster
{
public:
	SkeletonWarrior();
	~SkeletonWarrior();

	void Init() override;
	void Update() override;
	void Render() override;
};



