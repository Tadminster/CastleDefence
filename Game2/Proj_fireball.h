#pragma once
class Proj_fireball : public Projectile
{
private:
	//class ObCircle* explosionCol;

public:
	Proj_fireball(Vector2 spawnPos, Vector2 dir, float speed, float range, float damage, int penetration, float explosionRange);

	void Update() override;
	void Render() override;
};

