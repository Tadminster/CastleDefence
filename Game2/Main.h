#pragma once
class Main : public Scene
{
private:
	class Scene_1_title* sc_1_title;
	class Scene_2_inGame* sc_2_inGame;
	class Scene_3_death* sc_3_death;
	//class Map* mapManager;
	//class HUD* hud;

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
