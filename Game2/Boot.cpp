#include <string>

#include "stdafx.h"
#include "Item.h"
#include "Boot.h"

Boot::Boot()
{
	this->skin = new ObImage(L"Item_boot.png");
	this->tag = Tag::PASSIVE;

	this->level = 0;
	this->maxLevel = 10;

    this->name = L"   부츠";
    this->explain = L"이동속도: +15%";
}

void Boot::Update()
{
    GM->player->moveSpeed += 25;

    value = 15 * (level + 1);
    std::wstringstream ss;
    ss << L"이동속도: +" << this->value << L"%";
    this->explain = ss.str();
}
