#include <string>

#include "stdafx.h"
#include "Item.h"
#include "Boot.h"

Boot::Boot()
{
	this->skin = new ObImage(L"Item_boot.png");
	this->tag = Tag::PASSIVE;

	this->name = L"   부츠";
	this->explain = L"이동속도 증가";

	this->level = 0;
	this->maxLevel = 10;
}
