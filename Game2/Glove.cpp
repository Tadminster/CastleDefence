#include <string>

#include "stdafx.h"
#include "Item.h"
#include "Glove.h"

Glove::Glove()
{
	this->skin = new ObImage(L"Item_glove.png");
	this->tag = Tag::PASSIVE;

	this->level = 0;
	this->maxLevel = 10;

	this->name = L"   장갑";
	this->explain = L"공격속도: +15%";
}

void Glove::Update()
{
	GM->player->attSpeed += 0.15;

	value = 15 * (level + 1);
	std::wstringstream ss;
	ss << L"공격속도: +" << this->value << L"%";
	this->explain = ss.str();
}