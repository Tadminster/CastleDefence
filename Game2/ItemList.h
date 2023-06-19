#pragma once
class ItemList
{
public:
	int itemSize;

	// 무기류
	class Bow* bow;
	class Fireball* fireball;
	class ThrowingAxe* throwingAxe;

	// 패시브장비류
	class Boot* boot;
	class Glove* glove;
	class SharpEdge* sharpEdge;

	map<int, class Item*> itemList;

public:
	ItemList();
	void Init();

	Item* getItem(int number);
	
};

