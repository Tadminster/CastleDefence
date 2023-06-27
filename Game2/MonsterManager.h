#pragma once

class MonsterManager
{
private:
	vector<class Monster*> enemy;
	vector<class Projectile*> projectiles;

public:
	~MonsterManager() {}

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();

	vector<class Monster*>& getEnemy() { return enemy; }
	vector<class Projectile*>& getProjectiles() { return projectiles; }
	int		getEnemyCount() { return enemy.size(); }

	void	collisionsBetweenUnits();
	void	AddEnemy(Monster* monster);
	void	Relocation();
	void	Pool();
};

