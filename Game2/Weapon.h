#pragma once
class Weapon : public Item
{
protected:
	//wstring		name;
	//wstring		explain;
	float		attackSpeed;
	float		damage;
	float		projectileSpeed;
	float		range;
	float		critical;
	int			penetration;

	float		timeSinceLastTime;
	float		lastShotTime;

public:
	virtual ~Weapon() {}
	virtual bool Attack() = 0;
};

