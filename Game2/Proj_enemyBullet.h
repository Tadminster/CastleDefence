﻿#pragma once
class Proj_enemyBullet : public Projectile
{
public:
	Proj_enemyBullet(Vector2 spawnPos, Vector2 dir, float speed, float range, float damage, int penetration);

	void Update() override;
	void Render() override;
};

