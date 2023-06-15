#pragma once


class GameManager : public Singleton<GameManager>
{
public:
	class Player* player;
	class MonsterManager* monster;

	int kill = 0;
	// 경험치, row는 +1, col은 이전 row*2
	int nextExp[21] = {
						1,   3,   6,   10,  15,		// 1~5
						26,  38,  51,  65,  80,		// 11~15
						101, 123, 146, 170, 195,	// 21~25
						246, 298, 351, 405, 460, 
						9999999};	// 51~55
						
	
public:
	~GameManager();
	void Init();
	void Update();
};

