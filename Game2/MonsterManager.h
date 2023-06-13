#pragma once
#define MONSTER		MonsterManager::GetInstance()

class MonsterManager : public Singleton<MonsterManager>
{
private:
	vector<class Monster*> enemy;

public:
	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();


	int		getEnemyCount() { return enemy.size(); }

	void	AddEnemy(Monster* monster);
	void	Relocation();
	void	Pool();
};

