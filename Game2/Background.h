#pragma once
class Background
{
private:
	ObImage* bg_0;
	ObImage* bg_1;
	ObImage* bg_2;
	ObImage* bg_3;
	ObImage* bg_5;

	ObRect* shark_collider;
	ObImage* bg_4_shark;

public:
	Background();
	~Background();

	void Init();
	void Update();
	void LateUpdate();
	void Render(int type);

	void bg_left();
	void bg_right();
};