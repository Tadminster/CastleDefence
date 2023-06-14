#pragma once
enum class State
{
	IDLE,
	RUN
};

enum class Direction
{
	L,
	R
};

class Player
{
private:
	ObRect*			collider;
	ObRect*			collider_muzzle;
	ObRect*			area;

	ObImage*		skin_idle;
	ObImage*		skin_run;

	// state
	State			state;
	Direction		dir;

	vector<class Weapon*>		equip;
	vector<class Projectile>	projectiles;

	int				level;
	int				exp;

public:
	Player();
	~Player();

	ObRect*			getCollider()		{ return this->collider; }
	ObRect*			getColliderWeapon()	{ return this->collider_muzzle; }
	ObRect*			getArea()			{ return this->area; }
	virtual Vector2 getPos()			{ return this->collider->GetWorldPos(); }
	//State			getSate()		{ return this->state;}
	//Direction		getDir()		{ return this->dir;  }

	vector<class Projectile>& getProjectiles() {return projectiles;}

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Control();

};

