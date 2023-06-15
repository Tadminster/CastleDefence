#pragma once


class GameManager : public Singleton<GameManager>
{
public:
	class Player* player;
	class MonsterManager* monster;

	int kill;
	int level;
	int exp;
	int nextExp[];
	
public:
	~GameManager();
	void Init();
};

