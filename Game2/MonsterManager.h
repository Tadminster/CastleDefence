#pragma once

class MonsterManager
{
private:
	vector<class Monster*> enemy;

public:
	~MonsterManager() {}

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();

	vector<class Monster*>& getEnemy() { return enemy; }
	int		getEnemyCount() { return enemy.size(); }

	void	AddEnemy(Monster* monster);
	void	Relocation();
	void	Pool();
};

