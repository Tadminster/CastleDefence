#include "stdafx.h"
#include "Background.h"

Background::Background()
{
	bg_0 = new ObImage(L"bg_Background_0.png");
	bg_1 = new ObImage(L"bg_Background_1.png");
	bg_2 = new ObImage(L"bg_Background_2.png");
	bg_3 = new ObImage(L"bg_Background_3.png");
	bg_5 = new ObImage(L"bg_Background_5.png");

	shark_collider = new ObRect();
	bg_4_shark = new ObImage(L"shark.png");
	bg_4_shark->SetParentRT(*shark_collider);
}

Background::~Background()
{

	delete bg_0;
	delete bg_1;
	delete bg_2;
	delete bg_3;
	delete bg_4_shark;
	delete bg_5;
	TEXTURE->DeleteTexture(L"bg_Background_0.png");
	TEXTURE->DeleteTexture(L"bg_Background_1.png");
	TEXTURE->DeleteTexture(L"bg_Background_2.png");
	TEXTURE->DeleteTexture(L"bg_Background_3.png");
	TEXTURE->DeleteTexture(L"shark.png");
	TEXTURE->DeleteTexture(L"bg_Background_5.png");

	delete shark_collider;
}

void Background::Init()
{
	bg_0->scale.x = app.GetWidth();
	bg_0->scale.y = app.GetHeight();
	bg_1->scale.x = app.GetWidth();
	bg_1->scale.y = app.GetHeight();
	bg_2->scale.x = app.GetWidth();
	bg_2->scale.y = app.GetHeight();
	bg_3->scale.x = app.GetWidth();
	bg_3->scale.y = app.GetHeight();
	bg_5->scale.x = app.GetWidth();
	bg_5->scale.y = app.GetHeight();

	bg_5->uv.z = app.GetWidth() / bg_5->imageSize.x;

	bg_0->space = SPACE::SCREEN;
	bg_1->space = SPACE::SCREEN;
	bg_2->space = SPACE::SCREEN;
	bg_3->space = SPACE::SCREEN;
	bg_5->space = SPACE::SCREEN;

	bg_2->color = Color(0.60, 0.60, 0.60, 0.4f);
	bg_3->color = Color(0.65, 0.65, 0.65, 0.4f);
	bg_5->color = Color(0.60, 0.60, 0.60, 0.35f);

	shark_collider->scale.x = 1.0f;
	shark_collider->scale.y = 1.0f;
	bg_4_shark->SetWorldPosX(-1000);
	bg_4_shark->SetWorldPosY(-265);

	//bg_4_shark->SetParentRT(*this->collider);
	bg_4_shark->color = Color(0.6, 0.6, 0.6, 0.5);
	bg_4_shark->scale.x = bg_4_shark->imageSize.x / 5.0f;
	bg_4_shark->scale.y = bg_4_shark->imageSize.y ;
	bg_4_shark->uv.x = 1.0f / 5.0f;
	bg_4_shark->uv.z = 2.0f / 5.0f;
}

void Background::Update()
{
	bg_0->Update();
	bg_1->Update();
	bg_2->Update();
	bg_3->Update();
	bg_5->Update();

	static float tickCount = 0.0f;
	if (TIMER->GetTick(tickCount, 0.1f))
	{
		bg_4_shark->uv.z += 1.0f / 5.0f;
		bg_4_shark->uv.x += 1.0f / 5.0f;
	}
	shark_collider->MoveWorldPos(RIGHT * 550 * DELTA);
	shark_collider->Update();
	bg_4_shark->Update();
}

void Background::LateUpdate()
{
	// 상어 일정거리 멀어지면 위치 이동
	if (shark_collider->GetWorldPos().x > CAM->position.x + 2500)
		shark_collider->SetWorldPosX(CAM->position.x - 1000);
}

void Background::Render(int type)
{
	if (type == 0)
	{
		bg_0->Render();
		bg_1->Render();
		bg_2->Render();
		bg_3->Render();
	}
	else if (type == 1)
	{
		bg_4_shark->Render();
		bg_5->Render();
	}

}

void Background::bg_left()
{
	bg_0->uv.x -= DELTA * 10.0f / bg_0->imageSize.x;
	bg_0->uv.z -= DELTA * 10.0f / bg_0->imageSize.x;

	bg_1->uv.x -= DELTA * 20.0f / bg_1->imageSize.x;
	bg_1->uv.z -= DELTA * 20.0f / bg_1->imageSize.x;

	bg_2->uv.x -= DELTA * 30.0f / bg_2->imageSize.x;
	bg_2->uv.z -= DELTA * 30.0f / bg_2->imageSize.x;

	bg_3->uv.x -= DELTA * 50.0f / bg_3->imageSize.x;
	bg_3->uv.z -= DELTA * 50.0f / bg_3->imageSize.x;

	bg_5->uv.x -= DELTA * 100.0f / bg_5->imageSize.x;
	bg_5->uv.z -= DELTA * 100.0f / bg_5->imageSize.x;
}

void Background::bg_right()
{
	bg_0->uv.x += DELTA * 10.0f / bg_0->imageSize.x;
	bg_0->uv.z += DELTA * 10.0f / bg_0->imageSize.x;

	bg_1->uv.x += DELTA * 20.0f / bg_1->imageSize.x;
	bg_1->uv.z += DELTA * 20.0f / bg_1->imageSize.x;

	bg_2->uv.x += DELTA * 30.0f / bg_2->imageSize.x;
	bg_2->uv.z += DELTA * 30.0f / bg_2->imageSize.x;

	bg_3->uv.x += DELTA * 50.0f / bg_3->imageSize.x;
	bg_3->uv.z += DELTA * 50.0f / bg_3->imageSize.x;

	bg_5->uv.x += DELTA * 100.0f / bg_5->imageSize.x;
	bg_5->uv.z += DELTA * 100.0f / bg_5->imageSize.x;
}