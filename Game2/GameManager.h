#pragma once


class GameManager : public Singleton<GameManager>
{
public:
	bool	DEBUG_MODE = false;
	bool	isTitleEntering = true;

	//class   Title* title;
	class   HUD* hud;
	class	ItemList* itemList;
	class	LevelUp* levelUp;
	class	Player* player;
	class	MonsterManager* monster;

	bool lvUp = false;
	int kill = 0;
	// 경험치, row는 +1, col은 이전 row*2
	int nextExp[21] = {
						1,   3,   6,   10,  15,		// 1~5
						26,  38,  51,  65,  80,		// 11~15
						101, 123, 146, 170, 195,	// 21~25
						246, 298, 351, 405, 460,	// 31~35
						9999999};	// 51~55
	
	vector<unique_ptr<class ObImage>>	afterEffectManager;
	
public:
	~GameManager();
	void Init();
	void Update();
	void Render();
};

