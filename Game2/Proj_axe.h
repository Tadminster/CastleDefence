#pragma once
class Proj_axe : public Projectile
{
public:
	Proj_axe(Vector2 spawnPos, Vector2 dir, float speed, float range, float damage, int penetration);

	void Update() override;
	void Render() override;
};

