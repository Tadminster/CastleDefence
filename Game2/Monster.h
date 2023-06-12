#include "stdafx.h"
#pragma once
enum class MonsterDir
{
	U, D, L, R
};

class Monster
{
protected:
	ObRect* collider;
	ObImage* skin_run;
	MonsterDir dir;

public:
	//Monster() {};
	Monster();
	virtual ~Monster() {};

	virtual void Init();
	virtual void Update();
	virtual void Render();
};

