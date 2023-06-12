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

	void	AddEnemy(Monster* monster);

	int		getEnemyCount() { return enemy.size(); }
};

