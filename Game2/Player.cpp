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
	muzzle = new ObRect();
	area = new ObRect();
	
	skin_walk = new ObImage(L"player_walk.png");
	skin_roll = new ObImage(L"player_roll.png");

	playerTrail = new PlayerTrail();
}

Player::~Player()
{
	delete collider;
	delete muzzle;
	delete area;
	delete skin_walk;
	delete skin_roll;
	delete playerTrail;
	TEXTURE->DeleteTexture(L"player_walk.png");
	TEXTURE->DeleteTexture(L"player_roll.png");
}

void Player::Init()
{
	collider->SetWorldPos(Vector2(500, 500));
	action = PLAYER_ACTION::IDLE;
	dir_keyboard = PLAYER_DIRECTION::DIR_DOWN;
	dir_mouse = PLAYER_DIRECTION::DIR_DOWN;
	
	level = 0;
	exp = 0;
	maxHp = 50;
	hp = maxHp;
	damage = 1.0f;		
	def = 0;		
	attackSpeed = 1.0f;

	moveSpeed = 150;
	dashRange = 200;

	// COLLISION
	collider->scale = Vector2(30.0f, 60.f);
	collider->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	collider->isFilled = false;
	collider->hasAxis = false;

	// MUZZLE
	muzzle->SetParentRT(*collider);
	muzzle->scale.x = 30.0f;
	muzzle->scale.y = 3.0;
	muzzle->pivot = OFFSET_L;
	muzzle->isFilled = false;

	// AREA
	area->SetParentRT(*collider);
	area->scale = Vector2(1500.0f, 1500.0f);
	area->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	area->isFilled = false;
	area->hasAxis = false;

	// SKIN
	{	// WALK
		skin_walk->SetParentRT(*this->collider);
		skin_walk->scale.x = skin_walk->imageSize.x / skin_walk->maxFrame.x / 2;
		skin_walk->scale.y = skin_walk->imageSize.y / skin_walk->maxFrame.y / 2;
		skin_walk->maxFrame.x = 6;
		skin_walk->maxFrame.y = 8;
		skin_walk->ChangeAnim(ANIMSTATE::LOOP, 0.1);
	}

	{	// ROLL
		skin_roll->SetParentRT(*this->collider);
		skin_roll->scale.x = skin_roll->imageSize.x / skin_roll->maxFrame.x / 2;
		skin_roll->scale.y = skin_roll->imageSize.y / skin_roll->maxFrame.y / 2;
		skin_roll->maxFrame.x = 6;
		skin_roll->maxFrame.y = 8;
		skin_roll->ChangeAnim(ANIMSTATE::ONCE, 0.08);
	}

	playerTrail->Init();
}

void Player::Update()
{
	ImGui::Text("weapons : %i\n", this->equip.size());
	ImGui::Text("bullets : %i\n", this->projectiles.size());
	
	// 마우스 방향 계산
	Vector2 mouseDir = INPUT->GetWorldMousePos() - collider->GetWorldPos();
	int  mouseDirIndex = round((Utility::DirToRadian(mouseDir) + PI) / (45.0f * ToRadian));
	//ImGui::Text("mouse : %f\n", mouseDirIndex);

	if (mouseDirIndex == 0 || mouseDirIndex == 8)
		dir_mouse = PLAYER_DIRECTION::DIR_LEFT;
	else if (mouseDirIndex == 1)
		dir_mouse = PLAYER_DIRECTION::DIR_DOWN_LEFT;
	else if (mouseDirIndex == 2)
		dir_mouse = PLAYER_DIRECTION::DIR_DOWN;
	else if (mouseDirIndex == 3)
		dir_mouse = PLAYER_DIRECTION::DIR_DOWN_RIGHT;
	else if (mouseDirIndex == 4)
		dir_mouse = PLAYER_DIRECTION::DIR_RIGHT;
	else if (mouseDirIndex == 5)
		dir_mouse = PLAYER_DIRECTION::DIR_UP_RIGHT;
	else if (mouseDirIndex == 6)
		dir_mouse = PLAYER_DIRECTION::DIR_UP;
	else if (mouseDirIndex == 7)
		dir_mouse = PLAYER_DIRECTION::DIR_UP_LEFT;



	playerTrail->Update();

	// 플레이어 상태에 따른 작동
	if (status == PLAYER_STATUS::NORMAL)
	{
		if (skin_walk || skin_walk->color.x != 0.5)
			skin_walk->color = Vector4(0.5, 0.5, 0.5, 0.5);
	}
	else if (status == PLAYER_STATUS::DAMAGED)
	{
		if (timeOfDamage + 0.4f < TIMER->GetWorldTime())
		{
			status = PLAYER_STATUS::NORMAL;
		}
	}


	// 공격
	for (auto& att : equip)
		att->Attack();

	// 컨트롤
	this->Control();

	// 조준선 마우스 방향으로
	Vector2 mouse_point(INPUT->GetWorldMousePos() - this->muzzle->GetWorldPos());
	muzzle->rotation.z = atan2f(mouse_point.y, mouse_point.x);

	// 방향에 따른 스킨 y축 설정
	{
		// KEYBOARD
		switch (dir_keyboard)
		{
		case PLAYER_DIRECTION::DIR_RIGHT: skin_roll->frame.y = 0;
			break;
		case PLAYER_DIRECTION::DIR_UP: skin_roll->frame.y = 1;
			break;
		case PLAYER_DIRECTION::DIR_LEFT:skin_roll->frame.y = 2;
			break;
		case PLAYER_DIRECTION::DIR_DOWN: skin_roll->frame.y = 3;
			break;
		case PLAYER_DIRECTION::DIR_DOWN_RIGHT:skin_roll->frame.y = 4;
			break;
		case PLAYER_DIRECTION::DIR_DOWN_LEFT:skin_roll->frame.y = 5;
			break;
		case PLAYER_DIRECTION::DIR_UP_LEFT: skin_roll->frame.y = 6;
			break;
		case PLAYER_DIRECTION::DIR_UP_RIGHT:skin_roll->frame.y = 7;
			break;
		default:
			break;
		}

		// MOUSE
		switch (dir_mouse)
		{
		case PLAYER_DIRECTION::DIR_RIGHT: skin_walk->frame.y = 0;
			break;
		case PLAYER_DIRECTION::DIR_UP: skin_walk->frame.y = 1;
			break;
		case PLAYER_DIRECTION::DIR_LEFT:skin_walk->frame.y = 2;
			break;
		case PLAYER_DIRECTION::DIR_DOWN: skin_walk->frame.y = 3;
			break;
		case PLAYER_DIRECTION::DIR_DOWN_RIGHT:skin_walk->frame.y = 4;
			break;
		case PLAYER_DIRECTION::DIR_DOWN_LEFT:skin_walk->frame.y = 5;
			break;
		case PLAYER_DIRECTION::DIR_UP_LEFT: skin_walk->frame.y = 6;
			break;
		case PLAYER_DIRECTION::DIR_UP_RIGHT:skin_walk->frame.y = 7;
			break;
		default:
			break;
		}
	}

	// 정지시
	if (action == PLAYER_ACTION::IDLE)
	{
		skin_walk->frame.x = 0;
	}
	else if (action == PLAYER_ACTION::RUN)
	{
	}
	else if (action == PLAYER_ACTION::DASH)
	{
		if (dir_keyboard == PLAYER_DIRECTION::DIR_UP)
		{
			collider->MoveWorldPos(UP * dashRange * 5 * DELTA);
		}
		else if (dir_keyboard == PLAYER_DIRECTION::DIR_DOWN)
		{
			collider->MoveWorldPos(DOWN * dashRange * 5 * DELTA);
		}
		else if (dir_keyboard == PLAYER_DIRECTION::DIR_LEFT)
		{
			collider->MoveWorldPos(LEFT * dashRange * 5 * DELTA);
		}
		else if (dir_keyboard == PLAYER_DIRECTION::DIR_UP_LEFT)
		{
			collider->MoveWorldPos(UP * dashRange * 4 * DELTA);
			collider->MoveWorldPos(LEFT * dashRange * 4 * DELTA);
		}
		else if (dir_keyboard == PLAYER_DIRECTION::DIR_DOWN_LEFT)
		{
			collider->MoveWorldPos(DOWN * dashRange * 4 * DELTA);
			collider->MoveWorldPos(LEFT * dashRange * 4 * DELTA);
		}
		else if (dir_keyboard == PLAYER_DIRECTION::DIR_RIGHT)
		{
			collider->MoveWorldPos(RIGHT * dashRange * 5 * DELTA);
		}
		else if (dir_keyboard == PLAYER_DIRECTION::DIR_UP_RIGHT)
		{
			collider->MoveWorldPos(UP * dashRange * 4 * DELTA);
			collider->MoveWorldPos(RIGHT * dashRange * 4 * DELTA);
		}
		else if (dir_keyboard == PLAYER_DIRECTION::DIR_DOWN_RIGHT)
		{
			collider->MoveWorldPos(DOWN * dashRange * 4 * DELTA);
			collider->MoveWorldPos(RIGHT * dashRange * 4 * DELTA);
		}

		dashRange -= 600.0f * DELTA;

		if (dashRange < 0)
			action = PLAYER_ACTION::IDLE;
	}

	//탄이 몬스터와 충돌하면
	projectiles.erase(
	std::remove_if
	(
		projectiles.begin(),
		projectiles.end(),
		[](Projectile* pr) { return pr->hasCollideWithMonster(); }
	),
	projectiles.end()
	);

	// 탄이 일정거리 이상 벗어났으면 삭제
	projectiles.erase(
	std::remove_if
	(
		projectiles.begin(),
		projectiles.end(),
		[](Projectile* pr) { return pr->hasTraveledTooFar(); }
	),
	projectiles.end()
	);


	// 업데이트
	this->collider->Update();
	this->muzzle->Update();
	this->area->Update();
	this->skin_walk->Update();
	this->skin_roll->Update();

	// 탄 업데이트
	for (auto& projectiles : projectiles)
		projectiles->Update();
}

void Player::Render()
{
	if (GM->DEBUG_MODE)
	{
		this->muzzle->Render();
		this->collider->Render();
		this->area->Render();
	}

	if (action == PLAYER_ACTION::IDLE)
		skin_walk->Render();
	else if (action == PLAYER_ACTION::RUN)
		skin_walk->Render();
	else if (action == PLAYER_ACTION::DASH)
	{
		playerTrail->Render();
		skin_roll->Render();
	}


	for (auto& projectiles : projectiles)
		projectiles->Render();
}

void Player::Control()
{	

	// 이동
	if (action != PLAYER_ACTION::DASH)
	{
		if (INPUT->KeyUp('W') || INPUT->KeyUp('A') || INPUT->KeyUp('S') || INPUT->KeyUp('D'))
			action = PLAYER_ACTION::IDLE;

		if (INPUT->KeyPress('W') && INPUT->KeyPress('A'))
		{
			action = PLAYER_ACTION::RUN;
			dir_keyboard = PLAYER_DIRECTION::DIR_UP_LEFT;
			collider->MoveWorldPos(UP * moveSpeed * DELTA);
			collider->MoveWorldPos(LEFT * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('W') && INPUT->KeyPress('D'))
		{
			action = PLAYER_ACTION::RUN;
			dir_keyboard = PLAYER_DIRECTION::DIR_UP_RIGHT;
			collider->MoveWorldPos(UP * moveSpeed * DELTA);
			collider->MoveWorldPos(RIGHT * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('S') && INPUT->KeyPress('A'))
		{
			action = PLAYER_ACTION::RUN;
			dir_keyboard = PLAYER_DIRECTION::DIR_DOWN_LEFT;
			collider->MoveWorldPos(DOWN * moveSpeed * DELTA);
			collider->MoveWorldPos(LEFT * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('S') && INPUT->KeyPress('D'))
		{
			action = PLAYER_ACTION::RUN;
			dir_keyboard = PLAYER_DIRECTION::DIR_DOWN_RIGHT;
			collider->MoveWorldPos(DOWN * moveSpeed * DELTA);
			collider->MoveWorldPos(RIGHT * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('W'))
		{
			dir_keyboard = PLAYER_DIRECTION::DIR_UP;
			action = PLAYER_ACTION::RUN;
			collider->MoveWorldPos(UP * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('S'))
		{
			action = PLAYER_ACTION::RUN;
			dir_keyboard = PLAYER_DIRECTION::DIR_DOWN;
			collider->MoveWorldPos(DOWN * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('A'))
		{
			action = PLAYER_ACTION::RUN;
			dir_keyboard = PLAYER_DIRECTION::DIR_LEFT;
			collider->MoveWorldPos(LEFT * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('D'))
		{
			action = PLAYER_ACTION::RUN;
			dir_keyboard = PLAYER_DIRECTION::DIR_RIGHT;
			collider->MoveWorldPos(RIGHT * moveSpeed * DELTA);
		}

		// 대시
		if (INPUT->KeyDown(VK_SPACE))
		{
			dashRange = 200;
			action = PLAYER_ACTION::DASH;
			skin_roll->frame.x = 0;
		}
	}


}

void Player::actionsWhenDamaged(int value)
{
	// 상태를 데미지 받음으로 변경
	status = PLAYER_STATUS::DAMAGED;
	// 데미지 받은 시간 기록
	timeOfDamage = TIMER->GetWorldTime();
	// 스킨 컬러 변경
	skin_walk->color = Vector4(0.9, 0.5, 0.5, 0.5);
	// 데미지 차감
	int damage = max(value - def, 0);
	// 체력 감소
	hp = max(hp - damage, 0);
}