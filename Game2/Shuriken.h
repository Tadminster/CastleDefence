#pragma once
class Shuriken : public Weapon
{
private:

public:
	Shuriken();
	void Update() override;

	bool Attack() override;
};

