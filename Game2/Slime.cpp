#include "stdafx.h"
#include "Slime.h"

Slime::Slime()
{
	this->collider = new ObRect();
	this->skin_run = new ObImage(L"Slime.png");
	this->skin_run->SetParentRT(*this->collider);

	speed = 50;
}

Slime::~Slime()
{
	delete collider;
	delete skin_run;

	TEXTURE->DeleteTexture(L"Slime.png");
}

void Slime::Init()
{
	this->collider->SetWorldPos(Vector2(0, 0));
	this->collider->isFilled = false;

	this->collider->scale = Vector2(100, 100);
	this->skin_run->scale = Vector2(100, 100);
}

void Slime::Update()
{
	Monster::Update();
	//this->collider->Update();
	//this->skin_idle->Update();
	//this->skin_run->Update();
}

void Slime::Render()
{

	Monster::Render();
	//this->collider->Render();
	//this->skin_idle->Render();
	//this->skin_run->Render();
}