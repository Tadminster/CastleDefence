#pragma once
enum class MonsterDir
{
	U, D, L, R
};

enum class MonsterStatus
{
	NOMAL,
	DAMAGED
};

class Monster
{
protected:
	class ObRect* collider;
	class ObImage* skin_run;
	MonsterDir dir;
	MonsterStatus status;

	int		hp;
	float	speed;
	float	knockBackFactor;

public:
	float timeOfDamage;

public:
	// defalut
	Monster();
	virtual ~Monster() {};

	virtual void Init();
	virtual void Update();
	virtual void Render();

	// get
	virtual ObRect* getCollider() { return collider;}

	// set
	void			setHP(int value);
	/* 몬스터의 상태를 변경
	* PARAM type == 0, 일반적인 상태
	* PARAM type == 1, 데미지를 입었을 때 */
	void			setStatus(int type);

	// etc
	virtual void	Trace();
	virtual void	knockBack();
	/* 몬스터가 데미지 받았을 때 액션
	* PARAM Vector4.x = Damage, 
	* PARAM Vector4.y = knockBackFactor */
	void			actionsWhenDamaged(Vector4 value);
	bool            isDead() const { return hp == 0; }
};

