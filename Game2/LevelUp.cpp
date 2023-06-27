#include "stdafx.h"
#include "ItemList.h"
#include "Item.h"
#include "Weapon.h"
#include "LevelUp.h"

LevelUp::LevelUp()
{
	skin_window = new ObImage(L"skin_window_lvUp.png");

	for (int i = 0; i < 3; i++)
	{
		btn_col[i] = new ObRect();
		btn_skin[i] = new ObImage(L"btn_skin_col.png");
		btn_skin[i]->SetParentRT(*btn_col[i]);

		skin_item[i] = new ObImage(L"Item_00.png");
		skin_item[i]->SetParentRT(*btn_col[i]);

		items[i] = nullptr;
	}
}

LevelUp::~LevelUp()
{
	delete skin_window;
	for (int i = 0; i < 3; i++)
	{
		delete[] btn_col[i];
		delete[] btn_skin[i];

		delete[] skin_item[i];
	}
}

void LevelUp::Init()
{
	// 윈도우 창
	skin_window->scale = Vector2(950, 600);
	skin_window->color = Vector4(0.6, 0.6, 0.6, 0.45);

	textBox_lvUp.left = Utility::WorldToScreen(Vector2(0, 0)).x - 90;
	textBox_lvUp.top = Utility::WorldToScreen(Vector2(0, 0)).y - 270;
	textBox_lvUp.right = textBox_lvUp.left + 1000;
	textBox_lvUp.bottom = textBox_lvUp.top + 200;

	// 버튼
	for (int i = 0; i < 3; i++)
	{
		btn_col[i]->isFilled = false;
		btn_col[i]->scale = Vector2(270, 430);

		btn_skin[i]->scale = btn_col[i]->scale;
		btn_skin[i]->color = Vector4(0.55, 0.55, 0.55, 0.5);

		skin_item[i]->scale.x = 64;
		skin_item[i]->scale.y = 64;
		skin_item[i]->SetLocalPosY(120);
	}

	// 아이템 이름
	textBox_itemName[0].left = Utility::WorldToScreen(Vector2(-370, 0)).x;
	textBox_itemName[0].top = Utility::WorldToScreen(Vector2(0, 90)).y;
	textBox_itemName[0].right = textBox_itemName[0].left + 400;
	textBox_itemName[0].bottom = textBox_itemName[0].top + 400;

	textBox_itemName[1].left = Utility::WorldToScreen(Vector2(-70, 0)).x;
	textBox_itemName[1].top = Utility::WorldToScreen(Vector2(0, 90)).y;
	textBox_itemName[1].right = textBox_itemName[1].left + 400;
	textBox_itemName[1].bottom = textBox_itemName[1].top + 400;

	textBox_itemName[2].left = Utility::WorldToScreen(Vector2(230, 0)).x;
	textBox_itemName[2].top = Utility::WorldToScreen(Vector2(0, 90)).y;
	textBox_itemName[2].right = textBox_itemName[2].left + 400;
	textBox_itemName[2].bottom = textBox_itemName[2].top + 400;

	// 아이템 설명
	textBox_itemExplain[0].left = Utility::WorldToScreen(Vector2(-400, 0)).x;
	textBox_itemExplain[0].top = Utility::WorldToScreen(Vector2(0, 40)).y;
	textBox_itemExplain[0].right = textBox_itemExplain[0].left + 200;
	textBox_itemExplain[0].bottom = textBox_itemExplain[0].top + 400;

	textBox_itemExplain[1].left = Utility::WorldToScreen(Vector2(-100, 0)).x;
	textBox_itemExplain[1].top = Utility::WorldToScreen(Vector2(0, 40)).y;
	textBox_itemExplain[1].right = textBox_itemExplain[1].left + 200;
	textBox_itemExplain[1].bottom = textBox_itemExplain[1].top + 400;

	textBox_itemExplain[2].left = Utility::WorldToScreen(Vector2(200, 0)).x;
	textBox_itemExplain[2].top = Utility::WorldToScreen(Vector2(0, 40)).y;
	textBox_itemExplain[2].right = textBox_itemExplain[2].left + 200;
	textBox_itemExplain[2].bottom = textBox_itemExplain[2].top + 400;

	// 아이템 레벨
	textBox_itemLevel[0].left = Utility::WorldToScreen(Vector2(-400, 0)).x;
	textBox_itemLevel[0].top = Utility::WorldToScreen(Vector2(0, -190)).y;
	textBox_itemLevel[0].right = textBox_itemLevel[0].left + 200;
	textBox_itemLevel[0].bottom = textBox_itemLevel[0].top + 400;

	textBox_itemLevel[1].left = Utility::WorldToScreen(Vector2(-100, 0)).x;
	textBox_itemLevel[1].top = Utility::WorldToScreen(Vector2(0, -190)).y;
	textBox_itemLevel[1].right = textBox_itemLevel[1].left + 200;
	textBox_itemLevel[1].bottom = textBox_itemLevel[1].top + 400;

	textBox_itemLevel[2].left = Utility::WorldToScreen(Vector2(200, 0)).x;
	textBox_itemLevel[2].top = Utility::WorldToScreen(Vector2(0, -190)).y;
	textBox_itemLevel[2].right = textBox_itemLevel[2].left + 200;
	textBox_itemLevel[2].bottom = textBox_itemLevel[2].top + 400;
}

void LevelUp::Release()
{
}

void LevelUp::Update()
{

	skin_window->SetWorldPos(CAM->position);
	for (int i = 0; i < 3; i++)
	{
		btn_col[0]->SetWorldPos(Vector2(CAM->position.x - 300, CAM->position.y));
		btn_col[1]->SetWorldPos(Vector2(CAM->position.x, CAM->position.y));
		btn_col[2]->SetWorldPos(Vector2(CAM->position.x + 300, CAM->position.y));
	}

	for (int i = 0; i < 3; i++)
	{
		if (btn_col[i]->Intersect(INPUT->GetWorldMousePos()))
			btn_skin[i]->color = Vector4(0.7, 0.7, 0.7, 0.5);
		else if (btn_skin[i]->color.x != 0.55)
			btn_skin[i]->color = Vector4(0.55, 0.55, 0.55, 0.5);
	}

	skin_window->Update();
	for (auto& col : btn_col)
		col->Update();
	for (auto& col : btn_skin)
		col->Update();
	for (auto& skin : skin_item)
		skin->Update();
}

void LevelUp::LateUpdate()
{
}

void LevelUp::Render()
{
	skin_window->Render();
	if (GM->DEBUG_MODE)
	{
		for (auto& col : btn_col)
			col->Render();
	}

	for (auto& col : btn_skin)
		col->Render();
	for (auto& skin : skin_item)
		skin->Render();

	// 텍스트
	{
		// 레벨업 
		{
			DWRITE->RenderText(
		L"레벨 업!!",
		textBox_lvUp,
		45.0f,
		L"Neo둥근모",
		Color(0.9, 0.6, 0.2, 0.4),
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_ULTRA_EXPANDED);
		}

		// 아이템 이름
		{

			DWRITE->RenderText(
				items[0]->GetItemName(),
				textBox_itemName[0],
				26.0f,
				L"Neo둥근모",
				Color(0.8, 0.8, 0.8, 1),
				DWRITE_FONT_WEIGHT_BOLD,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_ULTRA_EXPANDED);

			DWRITE->RenderText(
				items[1]->GetItemName(),
				textBox_itemName[1],
				26.0f,
				L"Neo둥근모",
				Color(0.8, 0.8, 0.8, 1),
				DWRITE_FONT_WEIGHT_BOLD,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_ULTRA_EXPANDED);

			DWRITE->RenderText(
				items[2]->GetItemName(),
				textBox_itemName[2],
				26.0f,
				L"Neo둥근모",
				Color(0.8, 0.8, 0.8, 1),
				DWRITE_FONT_WEIGHT_BOLD,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_ULTRA_EXPANDED);
		}

		// 아이템 설명
		{
			DWRITE->RenderText(
				items[0]->GetItemexplain(),
				textBox_itemExplain[0],
				21.0f,
				L"Neo둥근모",
				Color(0.8, 0.8, 0.8, 1),
				DWRITE_FONT_WEIGHT_BOLD,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_ULTRA_EXPANDED);

			DWRITE->RenderText(
				items[1]->GetItemexplain(),
				textBox_itemExplain[1],
				21.0f,
				L"Neo둥근모",
				Color(0.8, 0.8, 0.8, 1),
				DWRITE_FONT_WEIGHT_BOLD,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_ULTRA_EXPANDED);

			DWRITE->RenderText(
				items[2]->GetItemexplain(),
				textBox_itemExplain[2],
				21.0f,
				L"Neo둥근모",
				Color(0.8, 0.8, 0.8, 1),
				DWRITE_FONT_WEIGHT_BOLD,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_ULTRA_EXPANDED);
		}

		// 아이템 레벨
		{
			DWRITE->RenderText(
				L"레벨 " + to_wstring(items[0]->level) + L"/" + to_wstring(items[0]->maxLevel),
				textBox_itemLevel[0],
				18.0f,
				L"Neo둥근모",
				Color(0.8, 0.8, 0.8, 1),
				DWRITE_FONT_WEIGHT_BOLD,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_ULTRA_EXPANDED);

			DWRITE->RenderText(
				L"레벨 " + to_wstring(items[1]->level) + L"/" + to_wstring(items[1]->maxLevel),
				textBox_itemLevel[1],
				18.0f,
				L"Neo둥근모",
				Color(0.8, 0.8, 0.8, 1),
				DWRITE_FONT_WEIGHT_BOLD,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_ULTRA_EXPANDED);

			DWRITE->RenderText(
				L"레벨 " + to_wstring(items[2]->level) + L"/" + to_wstring(items[2]->maxLevel),
				textBox_itemLevel[2],
				18.0f,
				L"Neo둥근모",
				Color(0.8, 0.8, 0.8, 1),
				DWRITE_FONT_WEIGHT_BOLD,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_ULTRA_EXPANDED);
		}
	}
}

int LevelUp::onClick()
{
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		if (btn_col[0]->Intersect(INPUT->GetWorldMousePos()))
		{
			LvEeventHandle(0);
			return 1;
		}
		if (btn_col[1]->Intersect(INPUT->GetWorldMousePos()))
		{
			LvEeventHandle(1);
			return 2;
		}
		if (btn_col[2]->Intersect(INPUT->GetWorldMousePos()))
		{
			LvEeventHandle(2);
			return 3;
		}

		return 0;
	}
}

bool LevelUp::GetRandomItem()
{
	int ran[3];
	while (true)
	{
		ran[0] = RANDOM->Int(1, GM->itemList->itemSize);
		ran[1] = RANDOM->Int(1, GM->itemList->itemSize);
		ran[2] = RANDOM->Int(1, GM->itemList->itemSize);

		if (ran[0] != ran[1] && ran[1] != ran[2] && ran[0] != ran[2]) break;
	}

	items[0] = GM->itemList->getItem(ran[0]);
	items[1] = GM->itemList->getItem(ran[1]);
	items[2] = GM->itemList->getItem(ran[2]);

	for (int i = 0; i < 3; i++)
	{
		skin_item[i] = items[i]->GetSkin();
		skin_item[i]->SetParentRT(*btn_col[i]);
		skin_item[i]->scale.x = 64;
		skin_item[i]->scale.y = 64;
		skin_item[i]->SetLocalPosY(140);
	}


	return true;
}

bool LevelUp::GetFirstItem()
{
	int ran[3];
	while (true)
	{
		ran[0] = RANDOM->Int(1, 3);
		ran[1] = RANDOM->Int(1, 3);
		ran[2] = RANDOM->Int(1, 3);

		if (ran[0] != ran[1] && ran[1] != ran[2] && ran[0] != ran[2]) break;
	}

	items[0] = GM->itemList->getItem(ran[0]);
	items[1] = GM->itemList->getItem(ran[1]);
	items[2] = GM->itemList->getItem(ran[2]);

	for (int i = 0; i < 3; i++)
	{
		skin_item[i] = items[i]->GetSkin();
		skin_item[i]->SetParentRT(*btn_col[i]);
		skin_item[i]->scale.x = 64;
		skin_item[i]->scale.y = 64;
		skin_item[i]->SetLocalPosY(140);
	}


	return true;
}

void LevelUp::LvEeventHandle(int number)
{
	if (items[number]->tag == Tag::WEAPON)
	{
		Weapon* weaponPtr = dynamic_cast<Weapon*>(items[number]);

		if (weaponPtr)
		{
			if (items[number]->level == 0)
			{
				GM->player->equip.emplace_back(weaponPtr);
			}

			weaponPtr->level++;
			weaponPtr->Update();
		}
	}
	else if (items[number]->tag == Tag::PASSIVE)
	{
		items[number]->level++;
		items[number]->Update();
	}


}
