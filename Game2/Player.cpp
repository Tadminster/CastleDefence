#include "stdafx.h"
#include "Weapon.h"
#include "Projectile.h"
#include "Player.h"

Player::Player()
{
	collider = new ObRect();
	collider_muzzle = new ObRect();
	collider_muzzle->SetParentRT(*collider);
	area = new ObRect();
	area->SetParentRT(*collider);
	
	skin_idle = new ObImage(L"player_idle_left.png");
	skin_run = new ObImage(L"player_run_left.png");

	this->Init();
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

	// COLLISION
	collider->scale = Vector2(30.0f, 60.f);
	collider->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	collider->isFilled = false;
	collider->hasAxis = false;

	// MUZZLE
	collider_muzzle->scale.x = 50.0f;
	collider_muzzle->scale.y = 3.0;
	collider_muzzle->pivot = OFFSET_L;
	collider_muzzle->isFilled = false;

	// AREA
	area->scale = Vector2(1500.0f, 1500.0f);
	area->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	area->isFilled = false;
	area->hasAxis = false;

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

void Player::Update()
{
	// 공격
	for (auto& att : equip)
		att->Attack();

	// 컨트롤
	this->Control();

	// 조준선 마우스 방향으로
	Vector2 mouse_point(INPUT->GetWorldMousePos() - this->collider_muzzle->GetWorldPos());
	collider_muzzle->rotation.z = atan2f(mouse_point.y, mouse_point.x);

	// 방향과 상태에 따른 설정
	if (dir == Direction::L)
	{
		skin_idle->reverseLR = false;
		skin_run->reverseLR = false;
		skin_run->SetLocalPosX(-10);
	}
	else if (dir == Direction::R)
	{
		skin_idle->reverseLR = true;
		skin_run->reverseLR = true;
		skin_run->SetLocalPosX(10);
	}

	if (state == State::IDLE)
	{
	}
	else if (state == State::RUN)
	{
		static float frameTick = 0.0f;
		if (TIMER->GetTick(frameTick, 0.1f))
				skin_run->frame.x += 1;
	}

	// 업데이트
	this->collider->Update();
	this->collider_muzzle->Update();
	this->area->Update();
	this->skin_idle->Update();
	this->skin_run->Update();
}

void Player::Render()
{
	if (DEBUG_MODE)
	{
		this->collider_muzzle->Render();
		this->collider->Render();
		this->area->Render();
	}

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
