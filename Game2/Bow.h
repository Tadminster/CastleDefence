#pragma once
class Bow : public Weapon
{
private:

public:
	Bow();
	void Update() override;

	bool Attack() override;
};

