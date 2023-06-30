#include <map>
#include <string>
#include <stdexcept>
#include <iostream>

#include "stdafx.h"

#include "Item.h"

#include "Weapon.h"
#include "Fireball.h"
#include "Bow.h"
#include "ThrowingAxe.h"
#include "Shuriken.h"

#include "Boot.h"
#include "Glove.h"
#include "SharpEdge.h"

#include "ItemList.h"

ItemList::ItemList() : itemSize(0)
{
	bow = new Bow();
	fireball = new Fireball();
	throwingAxe = new ThrowingAxe();
	shuriken = new Shuriken();

	boot = new Boot();
	glove = new Glove();
    sharpEdge = new SharpEdge();
}

void ItemList::Init()
{
	this->itemList.insert(std::make_pair(1, bow));
	this->itemList.insert(std::make_pair(2, fireball));
	this->itemList.insert(std::make_pair(3, throwingAxe));
	this->itemList.insert(std::make_pair(4, shuriken));

	this->itemList.insert(std::make_pair(5, boot));
	this->itemList.insert(std::make_pair(6, glove));
	this->itemList.insert(std::make_pair(7, sharpEdge));

    itemSize = itemList.size();
}

Item* ItemList::getItem(int number)
{
    try
    {
        return itemList.at(number);
    }
    catch (const std::out_of_range& e)
    {
        std::cout
            << "PATH ERROR, KEY =" + number << std::endl
            << "해당 키가 존재하지 않습니다." << std::endl;
    }
}


