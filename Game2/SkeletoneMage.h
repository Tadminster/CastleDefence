#pragma once
class SkeletoneMage : public Monster
{
public:
	SkeletoneMage();
	~SkeletoneMage();

	void Init() override;
	void Update() override;
	void Render() override;
};

