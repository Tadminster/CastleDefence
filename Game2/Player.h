#pragma once
enum class ImgState
{
	IDLE,
	RUN,
	DASH
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
	// collider
	ObRect*			collider;
	ObRect*			collider_muzzle;
	ObRect*			area;

	// skin
	ObImage*		skin_idle;
	ObImage*		skin_run;

	class PlayerTrail*	playerTrail;

	// state
	ImgState		state;
	Direction		dir;
	PlayerStatus	playerStatus;

	// trail

	vector<unique_ptr<class Projectile>>	projectiles;

	float	timeOfDamage;				// 데미지 받은 시간 기록
	
	float	hp;			// 체력
	float	maxHp;		// 최대체력
	float	dashRange;


public:
	vector<class Weapon*>		equip;
	vector<class Item*>			equipPassive;
	int				level;
	float			exp;

	float	damage;		// 공격력
	float	attSpeed;	// 공격속도
	float	def;		// 방어력
	float	moveSpeed;		// 이동속도


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
	ObImage*		getSkinScale()		{ return this->skin_run;}
	float			getHp()				{ return this->hp; }
	float			getMaxHp()			{ return this->maxHp; }
	float			getDamage()			{ return this->damage; }
	float			getAttSpeed()		{ return this->attSpeed; }
	float			getMoveSpeed()		{ return this->moveSpeed; }
	virtual Vector2 getPos()			{ return this->collider->GetWorldPos(); }
	vector<unique_ptr<class Projectile>>& getProjectiles() {return projectiles;}
	PlayerStatus	getPlayerStatus()	{ return playerStatus; }

	// set
	void			addAttSpeed(float value)	{ this->attSpeed + value; }
	void			addMoveSpeed(float value)	{ this->moveSpeed + value; }


	/* 데미지 받았을 때 액션
	* PARAM Vector4.x = Damage,
	* PARAM Vector4.y = knockBackFactor */
	void actionsWhenDamaged(int value);
};

