#pragma once
class HUD
{
private:
	class ObImage* exp_box;
	class ObImage* exp_gauge;

	class ObImage* hp_box;
	class ObImage* hp_gauge;

public:
	HUD();
	~HUD();
	void Init();
	void Release(); //해제
	void Update();
	void LateUpdate();//갱신
	void Render();
};

