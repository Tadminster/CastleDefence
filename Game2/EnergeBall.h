#pragma once
class EnergeBall : public Weapon
{
private:

public:
	EnergeBall();
	void Update() override;
	bool Attack() override;
};

