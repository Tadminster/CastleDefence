#pragma once
class Scene_1_title : public Scene
{
private:
	class ObImage* bg_title;
	class ObImage* skin_btnStart;
	class ObImage* skin_btnExit;
	class ObRect* btnStart;
	class ObRect* btnExit;

public:
	Scene_1_title();
	~Scene_1_title();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;


	void OnClick();
};

