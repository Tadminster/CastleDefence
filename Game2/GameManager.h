#pragma once


class GameManager : public Singleton<GameManager>
{
public:
	class Player* player;
	class MonsterManager* monster;
	
public:
	~GameManager();
	void Init();
};

