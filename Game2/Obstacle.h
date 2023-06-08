#pragma once
class Obstacle
{
private:
	ObRect* collider;
	ObImage* image_obstacle;

public:
	Obstacle();
	~Obstacle();

	void Init(float pos_x);
	void Update();
	void Render();
	void PushVector(vector<ObRect*>& obstacles);
};

