#pragma once
class LevelUp
{
private:
	ObImage* skin_window;

	ObRect* btn_col[3];
	ObImage* btn_skin[3];

	ObImage* skin_item[3];

	RECT textBox_lvUp;
	RECT textBox_itemName[3];
	RECT textBox_itemExplain[3];
	RECT textBox_itemLevel[3];

	class Item* items[3];

public:
	LevelUp();
	~LevelUp();
	void	Init();
	void	Release();		//해제
	void	Update();
	void	LateUpdate();	//갱신
	void	Render();

	int		onClick();
	bool	GetRandomItem();
	bool	GetFirstItem();
};
