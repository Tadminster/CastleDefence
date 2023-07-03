#pragma once
enum class PLAYER_ACTION
{
	IDLE,
	RUN,
	DASH,
	DEATH
};

enum class PLAYER_STATUS
{
	NORMAL,
	DAMAGED
};

enum class PLAYER_DIRECTION
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_UP_LEFT,
	DIR_DOWN_LEFT,
	DIR_RIGHT,
	DIR_UP_RIGHT,
	DIR_DOWN_RIGHT
};


class Player
{
private:
	// collider
	ObRect*				collider;
	ObRect*				muzzle;
	ObRect*				area;

	// skin
	ObImage*			skin_walk;
	ObImage*			skin_roll;
	ObImage*			skin_walkShadow;
	ObImage*			skin_rollShadow;
	ObImage*			skin_death;

	class PlayerTrail*	playerTrail;

	// state
	PLAYER_ACTION		action;
	PLAYER_STATUS		status;
	PLAYER_DIRECTION	dir_keyboard;
	PLAYER_DIRECTION	dir_mouse;

	// trail

	vector<class Projectile*>	projectiles;

	float	timeOfDamage;				// 데미지 받은 시간 기록
	
	float	hp;			// 체력
	float	maxHp;		// 최대체력
	float	dashRange;

	float   rolltime;

public:
	vector<class Weapon*>		equip;
	vector<class Item*>			equipPassive;
	int				level;
	float			exp;

	float	damage;			// 공격력
	float	attackSpeed;	// 공격속도
	float	def;			// 방어력
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
	ObRect*			getColliderWeapon()	{ return this->muzzle; }
	ObRect*			getArea()			{ return this->area; }
	ObImage*		getSkinWalk()		{ return this->skin_walk;}
	ObImage*		getSkinRoll()		{ return this->skin_roll;}
	float			getHp()				{ return this->hp; }
	float			getMaxHp()			{ return this->maxHp; }
	float			getDamage()			{ return this->damage; }
	float			getAttSpeed()		{ return this->attackSpeed; }
	float			getMoveSpeed()		{ return this->moveSpeed; }
	virtual Vector2 getPos()			{ return this->collider->GetWorldPos(); }
	vector<class Projectile*>& getProjectiles() {return projectiles;}
	PLAYER_STATUS	getPlayerStatus()	{ return status; }

	// set
	void			addAttSpeed(float value)	{ this->attackSpeed + value; }
	void			addMoveSpeed(float value)	{ this->moveSpeed + value; }


	/* 데미지 받았을 때 액션
	* PARAM Vector4.x = Damage,
	* PARAM Vector4.y = knockBackFactor */
	void actionsWhenDamaged(int value);
};

