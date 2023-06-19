#pragma once
class Proj_fireball : public Projectile
{
public:
	Proj_fireball(Vector2 spawnPos, Vector2 dir, float speed, float range, float damage);

	void Update() override;
	void Render() override;
};

