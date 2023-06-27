#pragma once
enum class MonsterDir
{
	U, D, L, R
};

enum class MonsterStatus
{
	NORMAL,
	DAMAGED
};

class Monster
{
protected:
	class ObRect* collider;
	class ObImage* skin_run;
	MonsterDir dir;
	MonsterStatus status;

	int		hp;						// 체력
	float	damage;					// 공격력
	float	defence;				// 방어력
	float	speed;					// 이동속도

	int		exp;					// 몬스터 킬 시 얻게되는 경험치
	float	knockBackFactor;		// 넉백에 사용되는 계수

	float timeOfDamage;				// 데미지 받은 시간 기록

public:
	// defalut
	Monster();
	virtual ~Monster() {};

	virtual void Init();
	virtual void Update();
	virtual void Render();

	// get
	virtual ObRect* getCollider() { return collider;}
	int				getExp() { return exp; }
	float			getDamage() { return damage; }

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

