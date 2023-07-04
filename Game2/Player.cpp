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
	skin_walkShadow = new ObImage(L"player_walk.png");
	skin_rollShadow = new ObImage(L"player_roll.png");
	skin_death = new ObImage(L"player_death.png");

	playerTrail = new PlayerTrail();
}

Player::~Player()
{
	delete collider;
	delete muzzle;
	delete area;
	delete skin_walk;
	delete skin_roll;
	delete skin_walkShadow;
	delete skin_rollShadow;
	delete skin_death;
	delete playerTrail;

	TEXTURE->DeleteTexture(L"player_walk.png");
	TEXTURE->DeleteTexture(L"player_roll.png");
	TEXTURE->DeleteTexture(L"player_death.png");
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
	collider->isFilled = false;
	collider->hasAxis = false;
	collider->pivot = OFFSET_B;
	collider->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	collider->scale = Vector2(30.0f, 60.f);

	// MUZZLE
	muzzle->SetParentRT(*collider);
	muzzle->isFilled = false;
	muzzle->pivot = OFFSET_L;
	muzzle->SetLocalPosY(collider->scale.y / 2.0f);
	muzzle->scale.x = 20.0f;
	muzzle->scale.y = 3.0;

	// AREA
	area->SetParentRT(*collider);
	area->scale = Vector2(2000.0f, 2000.0f);
	area->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	area->isFilled = false;
	area->hasAxis = false;

	// SKIN
	{	// WALK
		skin_walk->SetParentRT(*this->collider);
		skin_walk->pivot = OFFSET_B;
		skin_walk->maxFrame.x = 6;
		skin_walk->maxFrame.y = 8;
		skin_walk->scale.x = skin_walk->imageSize.x / skin_walk->maxFrame.x * 4;
		skin_walk->scale.y = skin_walk->imageSize.y / skin_walk->maxFrame.y * 4;
		skin_walk->ChangeAnim(ANIMSTATE::LOOP, 0.1);
	}

	{	// ROLL
		skin_roll->SetParentRT(*this->collider);
		skin_roll->pivot = OFFSET_B;
		skin_roll->maxFrame.x = 6;
		skin_roll->maxFrame.y = 8;
		skin_roll->scale.x = skin_roll->imageSize.x / skin_roll->maxFrame.x * 4;
		skin_roll->scale.y = skin_roll->imageSize.y / skin_roll->maxFrame.y * 4;
		skin_roll->ChangeAnim(ANIMSTATE::ONCE, 0.08);
	}

	{	// WALK SHADOW
		skin_walkShadow->SetParentRT(*this->collider);
		skin_walkShadow->pivot = OFFSET_B;
		skin_walkShadow->maxFrame.x = 6;
		skin_walkShadow->maxFrame.y = 8;
		skin_walkShadow->scale.x = skin_walkShadow->imageSize.x / skin_walkShadow->maxFrame.x * 4;
		skin_walkShadow->scale.y = skin_walkShadow->imageSize.y / skin_walkShadow->maxFrame.y * 4;
		skin_walkShadow->rotation.x = 80 * ToRadian;
		skin_walkShadow->color = Vector4(0, 0, 0, 0.25);
		skin_walkShadow->ChangeAnim(ANIMSTATE::LOOP, 0.1);
	}

	{	// ROLL SHADOW
		skin_rollShadow->SetParentRT(*this->collider);
		skin_rollShadow->pivot = OFFSET_B;
		skin_rollShadow->maxFrame.x = 6;
		skin_rollShadow->maxFrame.y = 8;
		skin_rollShadow->scale.x = skin_rollShadow->imageSize.x / skin_rollShadow->maxFrame.x * 4;
		skin_rollShadow->scale.y = skin_rollShadow->imageSize.y / skin_rollShadow->maxFrame.y * 4;
		skin_rollShadow->rotation.x = 80 * ToRadian;
		skin_rollShadow->color = Vector4(0, 0, 0, 0.25);
		skin_rollShadow->ChangeAnim(ANIMSTATE::ONCE, 0.08);
	}

	{
		// DEATH
		skin_death->SetParentRT(*this->collider);
		skin_death->pivot = OFFSET_B;
		skin_death->maxFrame.x = 12;
		skin_death->maxFrame.y = 1;
		skin_death->scale.x = skin_death->imageSize.x / skin_death->maxFrame.x;
		skin_death->scale.y = skin_death->imageSize.y / skin_death->maxFrame.y;
		skin_death->color.w = 0.3;
		skin_death->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	}

	playerTrail->Init();
}

void Player::Update()
{

	ImGui::Text("weapons : %i\n", this->equip.size());
	ImGui::Text("bullets : %i\n", this->projectiles.size());

	if (hp == 0) action = PLAYER_ACTION::DEATH;

	// 액션
	if (action == PLAYER_ACTION::DEATH)
	{
		static float elapsedDeathTime = 0.0f;
		elapsedDeathTime += DELTA;
		// 사망처리
		skin_death->Update();
		TIMER->TimeStop();

		if (elapsedDeathTime > 3.0f)
		{
			app.deltaScale = 0;
		}
	}
	else
	{

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
			case PLAYER_DIRECTION::DIR_RIGHT:
				skin_roll->frame.y = 0;
				skin_rollShadow->frame.y = 0;
				break;
			case PLAYER_DIRECTION::DIR_UP:
				skin_roll->frame.y = 1;
				skin_rollShadow->frame.y = 1;
				break;
			case PLAYER_DIRECTION::DIR_LEFT:
				skin_roll->frame.y = 2;
				skin_rollShadow->frame.y = 2;
				break;
			case PLAYER_DIRECTION::DIR_DOWN:
				skin_roll->frame.y = 3;
				skin_rollShadow->frame.y = 3;
				break;
			case PLAYER_DIRECTION::DIR_DOWN_RIGHT:
				skin_roll->frame.y = 4;
				skin_rollShadow->frame.y = 4;
				break;
			case PLAYER_DIRECTION::DIR_DOWN_LEFT:
				skin_roll->frame.y = 5;
				skin_rollShadow->frame.y = 5;
				break;
			case PLAYER_DIRECTION::DIR_UP_LEFT:
				skin_roll->frame.y = 6;
				skin_rollShadow->frame.y = 6;
				break;
			case PLAYER_DIRECTION::DIR_UP_RIGHT:
				skin_roll->frame.y = 7;
				skin_rollShadow->frame.y = 7;
				break;
			default:
				break;
			}

			// MOUSE
			switch (dir_mouse)
			{
			case PLAYER_DIRECTION::DIR_RIGHT:
				skin_walk->frame.y = 0;
				skin_walkShadow->frame.y = 0;
				break;
			case PLAYER_DIRECTION::DIR_UP:
				skin_walk->frame.y = 1;
				skin_walkShadow->frame.y = 1;
				break;
			case PLAYER_DIRECTION::DIR_LEFT:
				skin_walk->frame.y = 2;
				skin_walkShadow->frame.y = 2;
				break;
			case PLAYER_DIRECTION::DIR_DOWN:
				skin_walk->frame.y = 3;
				skin_walkShadow->frame.y = 3;
				break;
			case PLAYER_DIRECTION::DIR_DOWN_RIGHT:
				skin_walk->frame.y = 4;
				skin_walkShadow->frame.y = 4;
				break;
			case PLAYER_DIRECTION::DIR_DOWN_LEFT:
				skin_walk->frame.y = 5;
				skin_walkShadow->frame.y = 5;
				break;
			case PLAYER_DIRECTION::DIR_UP_LEFT:
				skin_walk->frame.y = 6;
				skin_walkShadow->frame.y = 6;
				break;
			case PLAYER_DIRECTION::DIR_UP_RIGHT:
				skin_walk->frame.y = 7;
				skin_walkShadow->frame.y = 7;
				break;
			default:
				break;
			}
		}

		if (action == PLAYER_ACTION::IDLE)
		{
			skin_walk->frame.x = 0;
			skin_walkShadow->frame.x = 0;
		}
		else if (action == PLAYER_ACTION::RUN)
		{
		}
		else if (action == PLAYER_ACTION::DASH)
		{
			switch (dir_keyboard)
			{
			case PLAYER_DIRECTION::DIR_UP:
				collider->MoveWorldPos(UP * DELTA * dashRange * 5);
				break;
			case PLAYER_DIRECTION::DIR_DOWN:
				collider->MoveWorldPos(DOWN * DELTA * dashRange * 5);
				break;
			case PLAYER_DIRECTION::DIR_LEFT:
				collider->MoveWorldPos(LEFT * DELTA * dashRange * 5);
				break;
			case PLAYER_DIRECTION::DIR_UP_LEFT:
				collider->MoveWorldPos(UP_LEFT * DELTA * dashRange * 4);
				break;
			case PLAYER_DIRECTION::DIR_DOWN_LEFT:
				collider->MoveWorldPos(DOWN_LEFT * DELTA * dashRange * 4);
				break;
			case PLAYER_DIRECTION::DIR_RIGHT:
				collider->MoveWorldPos(RIGHT * DELTA * dashRange * 5);
				break;
			case PLAYER_DIRECTION::DIR_UP_RIGHT:
				collider->MoveWorldPos(UP_RIGHT * DELTA * dashRange * 4);
				break;
			case PLAYER_DIRECTION::DIR_DOWN_RIGHT:
				collider->MoveWorldPos(DOWN_RIGHT * DELTA * dashRange * 4);
				break;
			default:
				break;
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
		this->skin_walkShadow->Update();
		this->skin_rollShadow->Update();
	}

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

	if (action == PLAYER_ACTION::DEATH)
	{
		skin_death->Render();
	}
	else if (action == PLAYER_ACTION::IDLE)
	{
		skin_walkShadow->Render();
		skin_walk->Render();
	}
	else if (action == PLAYER_ACTION::RUN)
	{
		skin_walkShadow->Render();
		skin_walk->Render();

	}
	else if (action == PLAYER_ACTION::DASH)
	{
		skin_rollShadow->Render();
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
			skin_rollShadow->frame.x = 0;

			rolltime = 0.0f;
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
	int damage = min(value + def, 0);
	// 체력 감소
	hp = max(hp + damage, 0);
}