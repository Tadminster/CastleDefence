#pragma once
#define GAME_MANAGER		GameManager::GetInstance()

class GameManager : public Singleton<GameManager>
{
private:

public:
	class Player* player;
	~GameManager();

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();


};

