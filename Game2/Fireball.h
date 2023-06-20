#pragma once
class Fireball : public Weapon
{
private:
	float explosionRange;

public:
	Fireball();
	void Update() override;

	bool Attack() override;
};

