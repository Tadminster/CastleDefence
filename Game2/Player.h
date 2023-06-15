#pragma once
enum class ImgState
{
	IDLE,
	RUN
};

enum class Direction
{
	L,
	R
};

enum class PlayerStatus
{
	NORMAL,
	DAMAGED
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
	ImgState		state;
	Direction		dir;
	PlayerStatus	playerStatus;

	vector<class Weapon*>		equip;
	vector<class Projectile>	projectiles;

	float timeOfDamage;				// 데미지 받은 시간 기록
	int		hp;			// 체력
	float	damage;		// 공격력
	float	def;		// 방어력
	float	speed;		// 이동속도

public:
	int				level;
	float			exp;



public:
	Player();
	~Player();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Control();

	// get
	ObRect*			getCollider()		{ return this->collider; }
	ObRect*			getColliderWeapon()	{ return this->collider_muzzle; }
	ObRect*			getArea()			{ return this->area; }
	virtual Vector2 getPos()			{ return this->collider->GetWorldPos(); }
	vector<class Projectile>& getProjectiles() {return projectiles;}
	PlayerStatus	getPlayerStatus() { return playerStatus; }

	/* 데미지 받았을 때 액션
	* PARAM Vector4.x = Damage,
	* PARAM Vector4.y = knockBackFactor */
	void actionsWhenDamaged(int value);
};

