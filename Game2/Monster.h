#pragma once
enum class MonsterDir
{
	U, D, L, R
};

class Monster
{
protected:
	class ObRect* collider;
	class ObImage* skin_run;
	MonsterDir dir;

	int		hp;
	float	speed;


public:
	// defalut
	Monster();
	virtual ~Monster() {};

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Trace();

	// get
	virtual ObRect* getCollider() { return collider;}

	// set
	void			SetHP(int value);

	// etc
	bool            isDead() const { return hp == 0; }
	void			knockBack(int value);
};

