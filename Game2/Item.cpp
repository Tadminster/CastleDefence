#include <string>

#include "stdafx.h"
#include "Item.h"

Item::Item() 
	: skin(new ObImage(L"Item_00.png")), tag(Tag::TBD),
	name(L"아이템"), explain(L"설명"),
	level(0), maxLevel(1) {};
