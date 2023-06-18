#include "stdafx.h"
#include "HUD.h"

#include <iomanip>

HUD::HUD()
{
	box_exp = new ObImage(L"ui_box_exp.png");
	gauge_exp = new ObImage(L"ui_gauge_exp.png");
	box_hp = new ObImage(L"ui_box_hp.png");
	gauge_hp = new ObImage(L"ui_gauge_hp.png");
	icon_kill = new ObImage(L"ui_icon_kill.png");

	gauge_exp->SetParentRT(*box_exp);
	gauge_hp->SetParentRT(*box_hp);

	box_exp->space = SPACE::SCREEN;
	gauge_exp->space = SPACE::SCREEN;
	box_hp->space = SPACE::SCREEN;
	gauge_hp->space = SPACE::SCREEN;
	icon_kill->space = SPACE::SCREEN;

	fontFile = "C:\\Users\\91bot\\source\\repos\\Tadminster\\CastleDefence\\Contents\\Fonts\\neodgm.ttf";
}

HUD::~HUD()
{
	delete box_exp;
	delete gauge_exp;
	delete box_hp;
	delete gauge_hp;
	delete icon_kill;
}

void HUD::Init()
{
	
	box_exp->pivot = OFFSET_L;
	box_exp->SetWorldPos(Vector2(-app.GetHalfWidth(), app.GetHalfHeight()-9));
	box_exp->scale.x = app.GetWidth();
	box_exp->scale.y = box_exp->imageSize.y * 2;

	gauge_exp->pivot = OFFSET_L;
	gauge_exp->scale.x = 0;
	gauge_exp->scale.y = box_exp->imageSize.y * 2;

	box_hp->pivot = OFFSET_L;
	box_hp->color = Vector4(0.5, 0.5, 0.5, 0.4);
	box_hp->SetWorldPos(Vector2(-50, -45));
	box_hp->scale.x = 100;
	box_hp->scale.y = box_hp->imageSize.y * 2;

	gauge_hp->pivot = OFFSET_L;
	gauge_hp->SetLocalPosX(3);
	gauge_hp->scale.x = 0;
	gauge_hp->scale.y = box_hp->imageSize.y * 2;

	icon_kill->pivot = OFFSET_L;
	icon_kill->SetWorldPos(Vector2(-app.GetHalfWidth() + 15, app.GetHalfHeight() - 50));
	icon_kill->scale.x = 32;
	icon_kill->scale.y = 32;

	textBox_kill.left = icon_kill->GetWorldPos().x + 60;
	textBox_kill.top = icon_kill->GetWorldPos().y + 27;
	textBox_kill.right = textBox_kill.left + 200;
	textBox_kill.bottom = textBox_kill.top + 200;

	textBox_level.left = Utility::WorldToScreen(Vector2(app.GetHalfWidth(), 0)).x - 90;
	textBox_level.top = Utility::WorldToScreen(Vector2(0, app.GetHalfHeight())).y + 27;
	textBox_level.right = textBox_level.left + 200;
	textBox_level.bottom = textBox_level.top + 200;

	textBox_time.left = Utility::WorldToScreen(Vector2(0, 0)).x - 60;
	textBox_time.top = Utility::WorldToScreen(Vector2(0, 0)).y - 450;
	textBox_time.right = textBox_time.left + 200;
	textBox_time.bottom = textBox_time.top + 200;
}

void HUD::Release()
{
}

void HUD::Update()
{
	gauge_exp->scale.x = (GM->player->exp / GM->nextExp[GM->player->level]) * app.GetWidth();
	gauge_hp->scale.x = (GM->player->getHp() / GM->player->getMaxHp()) * 94;

	box_exp->Update();
	gauge_exp->Update();
	box_hp->Update();
	gauge_hp->Update();
	icon_kill->Update();

	minute = TIMER->GetWorldTime() / 60;
	second = static_cast<int>(TIMER->GetWorldTime()) % 60;
}

void HUD::LateUpdate()
{
}

void HUD::Render()
{
	box_exp->Render();
	gauge_exp->Render();
	box_hp->Render();
	gauge_hp->Render();
	icon_kill->Render();

	// 킬
	DWRITE->RenderText(
		L"" + to_wstring(GM->kill), 
		textBox_kill, 
		30.0f, 
		L"HMFMMUEX", 
		Color(0.1, 0.1, 0.1, 1), 
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL, 
		DWRITE_FONT_STRETCH_ULTRA_EXPANDED);

	// 레벨
	DWRITE->RenderText(
		L"LV." + to_wstring(GM->player->level), 
		textBox_level, 
		30.0f, 
		L"HMFMMUEX", 
		Color(0.1, 0.1, 0.1, 1), 
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL, 
		DWRITE_FONT_STRETCH_ULTRA_EXPANDED);

	// 시간
	DWRITE->RenderText(
		wstring(2 - to_wstring(minute).length(), L'0') + to_wstring(minute) + L":" + wstring(2 - to_wstring(second).length(), L'0') + to_wstring(second),
		textBox_time, 
		50.0f, 
		L"HMFMMUEX", 
		Color(0.7, 0.7, 0.7, 1), 
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL, 
		DWRITE_FONT_STRETCH_ULTRA_EXPANDED);
}