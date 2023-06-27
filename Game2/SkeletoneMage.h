#pragma once
class SkeletoneMage : public Monster
{
private:
	ObCircle*	range[2];

public:
	SkeletoneMage();
	~SkeletoneMage();

	void Init() override;
	void Update() override;
	void Render() override;

	void attack() override;
};

