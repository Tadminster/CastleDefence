#pragma once
class HUD
{
private:
	class ObImage* box_exp;
	class ObImage* gauge_exp;

	class ObImage* box_hp;
	class ObImage* gauge_hp;

	class ObImage* icon_kill;

	RECT textBox_kill;
	RECT textBox_level;
	RECT textBox_time;
	
	string fontFile;
	int minute, second;

public:
	HUD();
	~HUD();
	void Init();
	void Release(); //해제
	void Update();
	void LateUpdate();//갱신
	void Render();
};

