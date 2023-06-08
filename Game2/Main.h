#pragma once
class Main : public Scene
{
private:
	/*ObImage* bg;
	ObImage* bg_1;
	ObImage* bg_2;
	ObImage* bg_3;
	ObImage* bg_4;*/
	bool gameStart;
	int score_cur;
	int score_max;

	
	class Map*		map;
	class Player*	player;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
