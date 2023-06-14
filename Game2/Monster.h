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
	//Monster() {};
	Monster();
	virtual ~Monster() {};

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Trace();

	virtual ObRect* getCollider() { return collider;}

	void			SetHP(int value);
	bool            isDead() const { return hp == 0; }
};

