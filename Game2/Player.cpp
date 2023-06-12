#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	collider = new ObRect();
	area = new ObRect();
	area->SetParentRT(*collider);
	
	skin_idle = new ObImage(L"player_idle_left.png");
	skin_run = new ObImage(L"player_run_left.png");

	// PLAYER COLLISION
	collider->scale = Vector2( 30.0f , 60.f);
	collider->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	collider->isFilled = false;
	collider->hasAxis = false;

	area->scale = Vector2(1500.0f, 1500.0f);
	area->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	area->isFilled = false;
	area->hasAxis = false;

	this->Init();

	// SKIN
	{
		// IDLE
		skin_idle->SetParentRT(*this->collider);
		skin_idle->scale.x = skin_idle->imageSize.x;
		skin_idle->scale.y = skin_idle->imageSize.y;

		// RUN
		skin_run->SetParentRT(*this->collider);
		skin_run->scale.x = skin_run->imageSize.x / 4.0f;
		skin_run->scale.y = skin_run->imageSize.y;
		skin_run->maxFrame.x = 4;
	}
}

Player::~Player()
{

	delete skin_idle;
	delete skin_run;
	TEXTURE->DeleteTexture(L"player_idel_left.png");
	TEXTURE->DeleteTexture(L"player_run_left.png");

	delete collider;
}

void Player::Init()
{
	collider->SetWorldPos(Vector2(0, 0));
	state = State::IDLE;
	dir = Direction::R;
}

void Player::Update()
{
	this->Control();
	this->collider->Update();
	this->area->Update();

	if (dir == Direction::L)
	{
		skin_idle->reverseLR = false;
		skin_run->reverseLR = false;
	}
	else if (dir == Direction::R)
	{
		skin_idle->reverseLR = true;
		skin_run->reverseLR = true;
	}

	if (state == State::IDLE)
	{
	}
	else if (state == State::RUN)
	{
		static float tickCount = 0.0f;
		if (TIMER->GetTick(tickCount, 0.1f))
				skin_run->frame.x += 1;
	}

	skin_idle->Update();
	skin_run->Update();
}

void Player::Render()
{
	this->collider->Render();
	this->area->Render();

	if (state == State::IDLE)
		skin_idle->Render();
	else if (state == State::RUN)
		skin_run->Render();
}

void Player::Control()
{	
	if (INPUT->KeyUp(VK_UP) || INPUT->KeyUp(VK_DOWN) || INPUT->KeyUp(VK_LEFT) || INPUT->KeyUp(VK_RIGHT))
		state = State::IDLE;

	// 방향
	//if (INPUT->KeyDown(VK_LEFT))
	//	dir = PlayerDir::L;
	//else if (INPUT->KeyDown(VK_RIGHT))
	//	dir = PlayerDir::R;

	// 이동
	if (INPUT->KeyPress(VK_UP))
	{
		state = State::RUN;
		collider->MoveWorldPos(UP * 200 * DELTA);
	}
	else if (INPUT->KeyPress(VK_DOWN))
	{
		state = State::RUN;
		collider->MoveWorldPos(DOWN * 200 * DELTA);
	}

	if (INPUT->KeyPress(VK_LEFT))
	{
		dir = Direction::L;
		state = State::RUN;
		collider->MoveWorldPos(LEFT * 200 * DELTA);
	}
	else if (INPUT->KeyPress(VK_RIGHT))
	{

		dir = Direction::R;
		state = State::RUN;
		collider->MoveWorldPos(RIGHT * 200 * DELTA);
	}
}
