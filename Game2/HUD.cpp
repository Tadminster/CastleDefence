#include "stdafx.h"
#include "HUD.h"

HUD::HUD()
{
	exp_box = new ObImage(L"ui_box_exp.png");
	exp_gauge = new ObImage(L"ui_gauge_exp.png");
	hp_box = new ObImage(L"ui_box_hp.png");
	hp_gauge = new ObImage(L"ui_gauge_hp.png");

	exp_gauge->SetParentRT(*exp_box);
	hp_gauge->SetParentRT(*hp_box);

	exp_box->space = SPACE::SCREEN;
	exp_gauge->space = SPACE::SCREEN;
	hp_box->space = SPACE::SCREEN;
	hp_gauge->space = SPACE::SCREEN;
}

HUD::~HUD()
{
	delete exp_box;
	delete exp_gauge;
	delete hp_box;
	delete hp_gauge;
}

void HUD::Init()
{
	
	exp_box->pivot = OFFSET_L;
	exp_box->SetWorldPos(Vector2(-app.GetHalfWidth(), app.GetHalfHeight()-9));
	exp_box->scale.x = app.GetWidth();
	exp_box->scale.y = exp_box->imageSize.y * 2;

	exp_gauge->pivot = OFFSET_L;
	exp_gauge->scale.x = 0;
	exp_gauge->scale.y = exp_box->imageSize.y * 2;
}

void HUD::Release()
{
}

void HUD::Update()
{
	exp_gauge->scale.x = (GM->player->exp / GM->nextExp[GM->player->level]) * app.GetWidth();

	exp_box->Update();
	exp_gauge->Update();
	hp_box->Update();
	hp_gauge->Update();
}

void HUD::LateUpdate()
{
}

void HUD::Render()
{
	exp_box->Render();
	exp_gauge->Render();
	hp_box->Render();
	hp_gauge->Render();
}