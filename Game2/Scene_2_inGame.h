#pragma once
class Scene_2_inGame : public Scene
{
private:
	class Map* mapManager;
	class HUD* hud;

public:
	Scene_2_inGame();
	~Scene_2_inGame();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

