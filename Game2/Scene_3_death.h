#pragma once
class Scene_3_death : public Scene
{
private:
	class ObImage* bg_death;
	class ObImage* skin_btnConfirm;
	class ObRect* btnConfirm;

public:
	Scene_3_death();
	~Scene_3_death();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void OnClick();
};

