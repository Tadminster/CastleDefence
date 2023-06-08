#pragma once
enum class PlayerState
{
	IDLE,
	RUN,
	JUMP
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
	ObImage*		skin_jump[2];

	// state
	PlayerState		state;
	PlayerDir		dir;

	// etc
	float			gravity;
	float			doubleJump;

public:
	Player();
	~Player();

	bool collision(class Map* map);

	ObRect*			getCollider()	{ return this->collider; }
	PlayerState		getSate()		{ return this->state;  }
	PlayerDir		getDir()		{ return this->dir;  }
	float			getGravity()	{ return this->gravity;  }

	void			setGravity(float value) { this->gravity += value; }

	virtual void Init();
	virtual void Update(Map* map);
	virtual void Render();
	virtual void Control();

	virtual Vector2 getPos() { return this->collider->GetWorldPos(); }
};

