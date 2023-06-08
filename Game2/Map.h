#pragma once
#define maxBlock 10

class Map
{
private:
	class Background* bg;
	class Floor* statPoint;
	class Floor** block;
	class Obstacle** obstacle;
	int blockCnt[maxBlock];
	int accumulatedDistance;

	vector<ObRect*> floors;
	vector<ObRect*> obstacles;

public:
	Map();
	~Map();
	
	void Init();
	void Update();
	void LateUpdate();
	/*
	* PARAM type == 0, BACK RENDER
	* PARAM type == 1, FRONT RENDER
	*/
	void Render(int type);


	void collision(class Player* target);
	vector<ObRect*>& getObjects() { return floors; }
	void relocate(Vector2 playerPos);

	/*
	* PARAM type == 0, LEFT PLAY
	* PARAM type == 1, RIGHT PLAY
	*/
	void play_bg(int type);
};

