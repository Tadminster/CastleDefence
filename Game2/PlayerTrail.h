#pragma once
class PlayerTrail
{
private:
	float       trialTime;
	float		trailTimer;
	deque<ObImage*> playerTrail;


public:
	PlayerTrail();
	~PlayerTrail();

	void Init();
	//void Release();
	void Update();
	//void LateUpdate();
	void Render();
	void Resize(int value);
};

