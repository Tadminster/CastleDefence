#pragma once
enum class PlayerState
{
	IDLE,
	RUN
};

enum class PlayerDir
{
	L,
	R
};

class Player
{
private:
	ObRect*			collider;
	ObImage*		skin_idle[2];
	ObImage*		skin_run[2];

	// state
	PlayerState		state;
	PlayerDir		dir;

public:
	Player();
	~Player();

	ObRect*			getCollider()	{ return this->collider; }
	PlayerState		getSate()		{ return this->state;  }
	PlayerDir		getDir()		{ return this->dir;  }

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Control();

	virtual Vector2 getPos() { return this->collider->GetWorldPos(); }
};

