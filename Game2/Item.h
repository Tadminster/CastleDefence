#pragma once
enum class Tag
{
	TBD,
	WEAPON,
	PASSIVE
};


class Item
{
protected:
	ObImage*			skin;
	std::wstring		name;
	std::wstring		explain;
	
public:
	int			level;
	int			maxLevel;
	Tag			tag;

public:
	Item();
	virtual ~Item() {};

	virtual void	Update() {};

	// get
	ObImage*		GetSkin()			{ return skin;  }
	std::wstring	GetItemName()		{ return name; };
	std::wstring	GetItemexplain()	{ return explain; };
};

