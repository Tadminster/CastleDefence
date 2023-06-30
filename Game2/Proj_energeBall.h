#pragma once
class Proj_energeBall : public Projectile
{
public:
	Proj_energeBall(Vector2 spawnPos, Vector2 dir, float speed, float range, float damage, int penetration);

	void Update() override;
	void Render() override;
};

