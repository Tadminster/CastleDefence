#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle()
{
	collider = new ObRect();
	collider-> pivot = OFFSET_LT;
	image_obstacle = new ObImage(L"obstacle.png");
	image_obstacle->SetParentRT(*collider);
	image_obstacle->pivot = OFFSET_LT;
}

Obstacle::~Obstacle()
{
	delete collider;
	delete image_obstacle;
	TEXTURE->DeleteTexture(L"obstacle.png");
}

void Obstacle::Init(float pos_x)
{
	collider->scale.x = 18.f;
	collider->scale.y = 48.f;
	if (RANDOM->Int())
		collider->SetWorldPos(Vector2(pos_x, -115));
	else 
		collider->SetWorldPos(Vector2(pos_x, -50));

	image_obstacle->scale.x = collider->scale.x;
	image_obstacle->scale.y = collider->scale.y;

	if (RANDOM->Int())
	{
		image_obstacle->uv.x = 6.0f / image_obstacle->imageSize.x;
		image_obstacle->uv.y = 8.0f / image_obstacle->imageSize.y;
		image_obstacle->uv.z = 10.0f / image_obstacle->imageSize.x;
		image_obstacle->uv.w = 24.0f / image_obstacle->imageSize.y;
	}
	else
	{
		image_obstacle->uv.x = 20.0f / image_obstacle->imageSize.x;
		image_obstacle->uv.y = 8.0f / image_obstacle->imageSize.y;
		image_obstacle->uv.z = 24.0f / image_obstacle->imageSize.x;
		image_obstacle->uv.w = 24.0f / image_obstacle->imageSize.y;
	}
}

void Obstacle::Update()
{
	collider->Update();
	image_obstacle->Update();
}

void Obstacle::Render()
{
	if (DEBUG_MODE)
		collider->Render();
	else
		image_obstacle->Render();
}

void Obstacle::PushVector(vector<ObRect*>& obstacles)
{
	obstacles.emplace_back(collider);
}
