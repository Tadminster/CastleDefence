#pragma once
class Proj_shuriken : public Projectile
{
public:
	Proj_shuriken(Vector2 spawnPos, Vector2 dir, float speed, float range, float damage, int penetration);

	void Update() override;
	void Render() override;

	bool hasCollideWithMonster() override;
	void findNewTarget();
};

