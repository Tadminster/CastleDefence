#include "stdafx.h"
#include "Slime.h"

Slime::Slime()
{
	this->collider = new ObRect();
	this->skin_run = new ObImage(L"Slime.png");
	this->skin_run->SetParentRT(*this->collider);

	speed = 40;
}

Slime::~Slime()
{
	delete collider;
	delete skin_run;

	TEXTURE->DeleteTexture(L"Slime.png");
}

void Slime::Init()
{
	this->collider->SetWorldPos(Vector2(RANDOM->Int(-1000, 1000), RANDOM->Int(-1000, 1000)));
	this->collider->isFilled = false;
	this->collider->scale = Vector2(30, 30);


	this->skin_run->scale = Vector2(75, 75);
	this->skin_run->maxFrame.x = 6;
	this->skin_run->maxFrame.y = 4;
}

void Slime::Update()
{
	Monster::Update();

	if (this->dir == MonsterDir::L)
	{
		this->skin_run->frame.y = 1;
	}
	else if (this->dir == MonsterDir::R)
	{
		this->skin_run->frame.y = 2;
	}
	else if (this->dir == MonsterDir::U)
	{
		this->skin_run->frame.y = 0;
	}
	else if (this->dir == MonsterDir::D)
	{
		this->skin_run->frame.y = 3;
	}
}

void Slime::Render()
{
	ImGui::Text("frame: %i\n", skin_run->frame.x);
	this->collider->Render();
	this->skin_run->Render();
	static float frameTick = 0.0f;
	if (TIMER->GetTick(frameTick, 0.4f))
	{
		skin_run->frame.x ++;

		if (skin_run->frame.x % skin_run->maxFrame.x == 0)
			skin_run->frame.x = 1;
	}
	//Monster::Render();
}