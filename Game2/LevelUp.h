#pragma once
class LevelUp
{
private:
	ObRect* btn_col[3];
	ObImage* btn_skin[3];

public:
	LevelUp();
	~LevelUp();
	void Init();
	void Release();		//해제
	void Update();
	void LateUpdate();	//갱신
	void Render();

	int onClick();
};
