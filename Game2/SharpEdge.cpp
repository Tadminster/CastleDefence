#include <string>

#include "stdafx.h"
#include "Item.h"
#include "SharpEdge.h"

SharpEdge::SharpEdge()
{
	this->skin = new ObImage(L"Item_damage.png");
	this->tag = Tag::PASSIVE;

	this->level = 0;
	this->maxLevel = 10;

	this->name = L"날카로운 칼날";
	this->explain = L"기본 데미지: +10%";
}

void SharpEdge::Update()
{
	GM->player->damage += 0.1f;

	value = 10 * (level + 1);
	std::wstringstream ss;
	ss << L"기본 데미지: +" << this->value << L"%";
	this->explain = ss.str();
}