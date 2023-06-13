#pragma once
class Weapon
{
protected:
	string		name;
	float		attackSpeed;
	float		damage;
	float		projectileSpeed;
	float		range;
	float		critical;

	float		timeSinceLastTime;
	float		lastShotTime;

public:
	virtual bool Attack() = 0;
};

