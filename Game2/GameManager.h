#pragma once


class GameManager : public Singleton<GameManager>
{
public:
	class Player* player;
	
public:
	~GameManager();
	void Init();
};

