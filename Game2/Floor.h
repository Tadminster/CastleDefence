#pragma once
class Floor
{
private:
	int midtiles;
	int tileInterval;

	ObRect**	mid;
	ObRect*		side_TOP[2];
	ObRect*		side_LR[2];

	ObImage**	mid_image;
	ObImage*	side_image[2];

public:
	Floor(int numberMidtiles);
	~Floor();

	void Init(float pos_x);
	void Update();
	void Render();
	void PushVector(vector<ObRect*>& floors, vector<ObRect*>& obstacles);
};

