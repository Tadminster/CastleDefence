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
	ObRect*			area;

	ObImage*		skin_idle;
	ObImage*		skin_run;

	// state
	State		state;
	Direction		dir;

public:
	Player();
	~Player();

	ObRect*			getCollider()	{ return this->collider; }
	ObRect*			getArea()		{ return this->area; }
	//State			getSate()		{ return this->state;}
	//Direction		getDir()		{ return this->dir;  }

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Control();

	virtual Vector2 getPos() { return this->collider->GetWorldPos(); }
};

