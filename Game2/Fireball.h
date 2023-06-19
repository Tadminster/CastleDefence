#pragma once
class Fireball : public Weapon
{
private:

public:
	Fireball();
	void Update() override;

	bool Attack() override;
};

