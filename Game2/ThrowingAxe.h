#pragma once
class ThrowingAxe : public Weapon
{
private:

public:
	ThrowingAxe();
	void Update() override;

	bool Attack() override;
};

