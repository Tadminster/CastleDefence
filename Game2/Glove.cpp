#include <string>

#include "stdafx.h"
#include "Item.h"
#include "Glove.h"

Glove::Glove()
{
	this->skin = new ObImage(L"Item_glove.png");
	this->tag = Tag::PASSIVE;

	this->name = L"   장갑";
	this->explain = L"공격속도 증가";

	this->level = 0;
	this->maxLevel = 10;
}
