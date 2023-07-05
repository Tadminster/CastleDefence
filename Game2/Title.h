#pragma once
class Title
{
private:
	class ObImage* bg_title;
	class ObImage* skin_btnStart;
	class ObImage* skin_btnExit;
	class ObRect* btnStart;
	class ObRect* btnExit;


public:
	Title();
	~Title();
	void Init();
	void Release(); //해제
	void Update();
	void LateUpdate();//갱신
	void Render();

	void OnClick();
};

