#include "stdafx.h"
#include "Player.h"
#include "Map.h"


Player::Player()
{
	collider = new ObRect();
	skin_idle[0] = new ObImage(L"player_idle_left.png");
	skin_idle[1] = new ObImage(L"player_idle_right.png");
	skin_run[0] = new ObImage(L"player_run_left.png");
	skin_run[1] = new ObImage(L"player_run_right.png");

	// PLAYER COLLISION
	collider->pivot = OFFSET_B;
	collider->scale.x = 30.0f;
	collider->scale.y = 60.0f;
	collider->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	collider->isFilled = false;
	collider->hasAxis = false;

	this->Init();

	// SKIN
	{
		// IDLE
		for (auto& idle : skin_idle)
		{
			idle->SetParentRT(*this->collider);
			idle->scale.x = idle->imageSize.x;
			idle->scale.y = idle->imageSize.y;
			idle->SetLocalPosY(34);
		}
		//skin_idle[0]->SetLocalPosX(-10);
		//skin_idle[1]->SetLocalPosX(10);

		// RUN
		for (auto& run : skin_run)
		{
			run->SetParentRT(*this->collider);
			run->scale.x = run->imageSize.x / 4.0f;
			run->scale.y = run->imageSize.y;
			run->uv.z = 1.0f / 4.0f;
			run->SetLocalPosY(34);
		}
		skin_run[0]->SetLocalPosX(-10);
		skin_run[1]->SetLocalPosX(10);
	}
}

Player::~Player()
{
	for (auto& idle : skin_idle)
		delete idle;
	TEXTURE->DeleteTexture(L"player_idel_left.png");
	TEXTURE->DeleteTexture(L"player_idel_right.png");

	for (auto& run : skin_run)
		delete run;
	TEXTURE->DeleteTexture(L"player_run_left.png");
	TEXTURE->DeleteTexture(L"player_run_right.png");

	delete collider;
}

void Player::Init()
{
	collider->SetWorldPos(Vector2(0, 0));
	state = PlayerState::IDLE;
	dir = PlayerDir::R;
}

void Player::Update()
{
	this->Control();
	this->collider->Update();

	if (state != PlayerState::IDLE)
	{
	}
	else if (state == PlayerState::RUN)
	{
		static float tickCount = 0.0f;
		if (TIMER->GetTick(tickCount, 0.1f))
			for (auto& playerSkin : this->skin_run)
			{
				playerSkin->uv.z += 1.0f / 4.0f;
				playerSkin->uv.x += 1.0f / 4.0f;
			}
	}



	//static float tickCount = 0.0f;
	//if (TIMER->GetTick(tickCount, 0.1f))
	//{
	//	if (INPUT->KeyPress(VK_LEFT))
	//	{
	//		
	//		for (auto& playerSkin : this->skin_run)
	//		{
	//			playerSkin->uv.z -= 1.0f / 4.0f;
	//			playerSkin->uv.x -= 1.0f / 4.0f;
	//		}
	//	}
	//	if (INPUT->KeyPress(VK_RIGHT))
	//	{
	//		for (auto& playerSkin : this->skin_run)
	//		{
	//			playerSkin->uv.z += 1.0f / 4.0f;
	//			playerSkin->uv.x += 1.0f / 4.0f;
	//		}
	//	}

	//}

	for (auto& idle : this->skin_idle)
		idle->Update();
	for (auto& run : this->skin_run)
		run->Update();
}

void Player::Render()
{
	this->collider->Render();

	if (state == PlayerState::IDLE && dir == PlayerDir::L)
		skin_idle[0]->Render();
	else if (state == PlayerState::IDLE && dir == PlayerDir::R)
		skin_idle[1]->Render();

	else if (state == PlayerState::RUN && dir == PlayerDir::L)
		skin_run[0]->Render();
	else if (state == PlayerState::RUN && dir == PlayerDir::R)
		skin_run[1]->Render();


}

void Player::Control()
{	
	// 상태
	if (INPUT->KeyDown(VK_UP) || INPUT->KeyDown(VK_DOWN) || INPUT->KeyDown(VK_LEFT) || INPUT->KeyDown(VK_RIGHT))
		state = PlayerState::RUN;
	if (INPUT->KeyUp(VK_UP) || INPUT->KeyDown(VK_DOWN) || INPUT->KeyDown(VK_LEFT) || INPUT->KeyDown(VK_RIGHT))
		state = PlayerState::IDLE;

	// 방향
	if (INPUT->KeyDown(VK_LEFT))
		dir = PlayerDir::L;
	else if (INPUT->KeyDown(VK_RIGHT))
		dir = PlayerDir::R;

	// 이동
	if (INPUT->KeyPress(VK_UP))
		collider->MoveWorldPos(UP * 500 * DELTA);
	else if (INPUT->KeyPress(VK_DOWN))
		collider->MoveWorldPos(DOWN * 500 * DELTA);

	if (INPUT->KeyPress(VK_LEFT))
		collider->MoveWorldPos(LEFT * 500 * DELTA);
	else if (INPUT->KeyPress(VK_RIGHT))
		collider->MoveWorldPos(RIGHT * 500 * DELTA);
}
