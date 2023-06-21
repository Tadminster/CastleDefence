#include "stdafx.h"
#include "Item.h"
#include "Weapon.h"
#include "Fireball.h"
#include "Bow.h"
#include "ThrowingAxe.h"
#include "Projectile.h"
#include "PlayerTrail.h"
#include "Player.h"

Player::Player()
{
	collider = new ObRect();
	collider_muzzle = new ObRect();
	collider_muzzle->SetParentRT(*collider);
	area = new ObRect();
	area->SetParentRT(*collider);
	
	skin = new ObImage(L"player_mage.png");
	//skin_idle = new ObImage(L"player_idle_left.png");
	//skin_run = new ObImage(L"player_run_left.png");

	playerTrail = new PlayerTrail();
}

Player::~Player()
{
	delete skin;
	TEXTURE->DeleteTexture(L"player_mage.png");

	//delete skin_idle;
	//delete skin_run;
	//TEXTURE->DeleteTexture(L"player_idel_left.png");
	//TEXTURE->DeleteTexture(L"player_run_left.png");

	delete collider;
}

void Player::Init()
{
	collider->SetWorldPos(Vector2(500, 500));
	state = ImgState::IDLE;
	dir = Direction::PLAYER_DIR_DOWN;
	
	level = 0;
	exp = 0;
	maxHp = 50;
	hp = maxHp;
	damage = 1.0f;		
	def = 0;		
	attSpeed = 1.0f;

	moveSpeed = 150;
	dashRange = 200;

	// COLLISION
	collider->scale = Vector2(30.0f, 60.f);
	collider->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	collider->isFilled = false;
	collider->hasAxis = false;

	// MUZZLE
	collider_muzzle->scale.x = 30.0f;
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
		skin->SetParentRT(*this->collider);
		skin->scale.x = skin->imageSize.x / 4.0f * 3.5;
		skin->scale.y = skin->imageSize.y / 8.0f * 3.5;
		skin->maxFrame.x = 4;
		skin->maxFrame.y = 8;

		// IDLE
		//skin_idle->SetParentRT(*this->collider);
		//skin_idle->scale.x = skin_idle->imageSize.x;
		//skin_idle->scale.y = skin_idle->imageSize.y;

		// RUN
		//skin_run->SetParentRT(*this->collider);
		//skin_run->scale.x = skin_run->imageSize.x / 4.0f;
		//skin_run->scale.y = skin_run->imageSize.y;
		//skin_run->maxFrame.x = 4;
	}

	playerTrail->Init();
	//equip.emplace_back(new Fireball());
	//equip.emplace_back(new ThrowingAxe());
}

void Player::Update()
{
	ImGui::Text("weapons : %i\n", this->equip.size());
	ImGui::Text("bullets : %i\n", this->projectiles.size());
	ImGui::Text("col_weapon : %f\n", this->collider_muzzle->GetRight().x);
	ImGui::Text("col_weapon : %f\n", this->collider_muzzle->GetRight().y);

	playerTrail->Update();

	// 플레이어 상태에 따른 작동
	if (playerStatus == PlayerStatus::NORMAL)
	{
		if (skin || skin->color.x != 0.5)
			skin->color = Vector4(0.5, 0.5, 0.5, 0.5);

		//if (skin_run || skin_run->color.x != 0.5)
		//	skin_run->color = Vector4(0.5, 0.5, 0.5, 0.5);
		//if (skin_idle || skin_idle->color.x != 0.5)
		//	skin_idle->color = Vector4(0.5, 0.5, 0.5, 0.5);
	}
	else if (playerStatus == PlayerStatus::DAMAGED)
	{
		if (timeOfDamage + 0.4f < TIMER->GetWorldTime())
		{
			playerStatus = PlayerStatus::NORMAL;
		}
	}


	// 공격
	for (auto& att : equip)
		att->Attack();

	// 컨트롤
	this->Control();

	// 조준선 마우스 방향으로
	Vector2 mouse_point(INPUT->GetWorldMousePos() - this->collider_muzzle->GetWorldPos());
	collider_muzzle->rotation.z = atan2f(mouse_point.y, mouse_point.x);

	// 방향에 따른 스킨 y축 설정
	if (dir == Direction::PLAYER_DIR_DOWN)
	{
		skin->frame.y = 0;
	}
	else if (dir == Direction::PLAYER_DIR_RIGHT_DOWN)
	{
		skin->frame.y = 1;
	}
	else if (dir == Direction::PLAYER_DIR_RIGHT)
	{
		skin->frame.y = 2;
	}
	else if (dir == Direction::PLAYER_DIR_RIGHT_UP)
	{
		skin->frame.y = 3;
	}
	else if (dir == Direction::PLAYER_DIR_UP)
	{
		skin->frame.y = 4;
	}
	else if (dir == Direction::PLAYER_DIR_LEFT_UP)
	{
		skin->frame.y = 5;
	}
	else if (dir == Direction::PLAYER_DIR_LEFT)
	{
		skin->frame.y = 6;
		//skin_idle->reverseLR = false;
		//skin_run->reverseLR = false;
		//skin_run->SetLocalPosX(-10);
	}
	else if (dir == Direction::PLAYER_DIR_LEFT_DOWN)
	{
		skin->frame.y = 7;
		//skin_idle->reverseLR = false;
		//skin_run->reverseLR = false;
		//skin_run->SetLocalPosX(-10);
	}

	if (state == ImgState::IDLE)
	{
		skin->frame.x = 0;
	}
	else if (state == ImgState::RUN)
	{
		static float frameTick = 0.0f;
		if (TIMER->GetTick(frameTick, 0.1f))
				skin->frame.x += 1;
				//skin_run->frame.x += 1;
	}
	else if (state == ImgState::DASH)
	{
		if (dir == Direction::PLAYER_DIR_UP)
		{
			collider->MoveWorldPos(UP * dashRange * 5 * DELTA);
		}
		else if (dir == Direction::PLAYER_DIR_DOWN)
		{
			collider->MoveWorldPos(DOWN * dashRange * 5 * DELTA);
		}
		else if (dir == Direction::PLAYER_DIR_LEFT)
		{
			collider->MoveWorldPos(LEFT * dashRange * 5 * DELTA);
		}
		else if (dir == Direction::PLAYER_DIR_LEFT_UP)
		{
			collider->MoveWorldPos(UP * dashRange * 4 * DELTA);
			collider->MoveWorldPos(LEFT * dashRange * 4 * DELTA);
		}
		else if (dir == Direction::PLAYER_DIR_LEFT_DOWN)
		{
			collider->MoveWorldPos(DOWN * dashRange * 4 * DELTA);
			collider->MoveWorldPos(LEFT * dashRange * 4 * DELTA);
		}
		else if (dir == Direction::PLAYER_DIR_RIGHT)
		{
			collider->MoveWorldPos(RIGHT * dashRange * 5 * DELTA);
		}
		else if (dir == Direction::PLAYER_DIR_RIGHT_UP)
		{
			collider->MoveWorldPos(UP * dashRange * 4 * DELTA);
			collider->MoveWorldPos(RIGHT * dashRange * 4 * DELTA);
		}
		else if (dir == Direction::PLAYER_DIR_RIGHT_DOWN)
		{
			collider->MoveWorldPos(DOWN * dashRange * 4 * DELTA);
			collider->MoveWorldPos(RIGHT * dashRange * 4 * DELTA);
		}

		dashRange -= 600.0f * DELTA;

		if (dashRange < 0)
			state = ImgState::IDLE;
	}



	 //탄이 몬스터와 충돌하면
	projectiles.erase(
	std::remove_if
	(
		projectiles.begin(),
		projectiles.end(),
		[](unique_ptr<Projectile>& pr) { return pr->hasCollideWithMonster(); }
	),
	projectiles.end()
	);

	// 탄이 일정거리 이상 벗어났으면 삭제
	projectiles.erase(
	std::remove_if
	(
		projectiles.begin(),
		projectiles.end(),
		[](unique_ptr<Projectile>& pr) { return pr->hasTraveledTooFar(); }
	),
	projectiles.end()
	);


	// 업데이트
	this->collider->Update();
	this->collider_muzzle->Update();
	this->area->Update();
	this->skin->Update();
	//this->skin_idle->Update();
	//this->skin_run->Update();

	// 탄 업데이트
	for (auto& projectiles : projectiles)
		projectiles->Update();
}

void Player::Render()
{
	if (DEBUG_MODE)
	{
		this->collider_muzzle->Render();
		this->collider->Render();
		this->area->Render();
	}

	if (state == ImgState::IDLE)
		skin->Render();
		//skin_idle->Render();
	else if (state == ImgState::RUN)
		skin->Render();
		//skin_run->Render();
	else if (state == ImgState::DASH)
	{
		skin->Render();
		//skin_run->Render();
		playerTrail->Render();
	}


	for (auto& projectiles : projectiles)
		projectiles->Render();
}

void Player::Control()
{	




	// 방향
	//if (INPUT->KeyDown(VK_LEFT))
	//	dir = PlayerDir::L;
	//else if (INPUT->KeyDown(VK_RIGHT))
	//	dir = PlayerDir::R;

	// 이동
	if (state != ImgState::DASH)
	{
		if (INPUT->KeyUp('W') || INPUT->KeyUp('A') || INPUT->KeyUp('S') || INPUT->KeyUp('D'))
			state = ImgState::IDLE;

		if (INPUT->KeyPress('W') && INPUT->KeyPress('A'))
		{
			state = ImgState::RUN;
			dir = Direction::PLAYER_DIR_LEFT_UP;
			collider->MoveWorldPos(UP * moveSpeed * DELTA);
			collider->MoveWorldPos(LEFT * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('W') && INPUT->KeyPress('D'))
		{
			state = ImgState::RUN;
			dir = Direction::PLAYER_DIR_RIGHT_UP;
			collider->MoveWorldPos(UP * moveSpeed * DELTA);
			collider->MoveWorldPos(RIGHT * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('S') && INPUT->KeyPress('A'))
		{
			state = ImgState::RUN;
			dir = Direction::PLAYER_DIR_LEFT_DOWN;
			collider->MoveWorldPos(DOWN * moveSpeed * DELTA);
			collider->MoveWorldPos(LEFT * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('S') && INPUT->KeyPress('D'))
		{
			state = ImgState::RUN;
			dir = Direction::PLAYER_DIR_RIGHT_DOWN;
			collider->MoveWorldPos(DOWN * moveSpeed * DELTA);
			collider->MoveWorldPos(RIGHT * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('W'))
		{
			dir = Direction::PLAYER_DIR_UP;
			state = ImgState::RUN;
			collider->MoveWorldPos(UP * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('S'))
		{
			state = ImgState::RUN;
			dir = Direction::PLAYER_DIR_DOWN;
			collider->MoveWorldPos(DOWN * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('A'))
		{
			state = ImgState::RUN;
			dir = Direction::PLAYER_DIR_LEFT;
			collider->MoveWorldPos(LEFT * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('D'))
		{
			state = ImgState::RUN;
			dir = Direction::PLAYER_DIR_RIGHT;
			collider->MoveWorldPos(RIGHT * moveSpeed * DELTA);
		}

		// 대시
		if (INPUT->KeyDown(VK_SPACE))
		{
			dashRange = 200;
			state = ImgState::DASH;
		}
	}


}

void Player::actionsWhenDamaged(int value)
{
	cout << "충돌" << endl;

	// 상태를 데미지 받음으로 변경
	playerStatus = PlayerStatus::DAMAGED;
	// 데미지 받은 시간 기록
	timeOfDamage = TIMER->GetWorldTime();
	// 스킨 컬러 변경
	skin->color = Vector4(0.9, 0.5, 0.5, 0.5);
	//skin_run->color = Vector4(0.9, 0.5, 0.5, 0.5);
	//skin_idle->color = Vector4(0.9, 0.5, 0.5, 0.5);
	// 데미지 차감
	int damage = max(value - def, 0);
	// 체력 감소
	hp = max(hp - damage, 0);
}