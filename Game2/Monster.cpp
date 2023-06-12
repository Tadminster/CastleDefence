#include "Monster.h"

Monster::Monster() :
	collider(new ObRect()), 
	skin_run(nullptr),
	dir(MonsterDir::D)
	{}

void Monster::Init()
{
}

void Monster::Update()
{
	this->collider->Update();

	if (this->skin_run)
		this->skin_run->Update();
}

void Monster::Render()
{
	this->collider->Render();

	if (this->skin_run)
		this->skin_run->Render();
}
