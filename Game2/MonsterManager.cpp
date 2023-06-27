#include "stdafx.h"
#include "Monster.h"
#include "Slime.h"
#include "KingSlime.h"
#include "MegaSlime.h"
#include "KingMegaSlime.h"
#include "MonsterManager.h"

void MonsterManager::Init()
{
	Slime* slime[10];
	for (int i = 0; i < 10; i++)
	{
		slime[i] = new Slime();
		slime[i]->Init();
		GM->monster->AddEnemy(slime[i]);
	}
}

void MonsterManager::Release()
{
}

void MonsterManager::Update()
{
	// 체력이 0되는 몬스터 삭제
	enemy.erase(
		std::remove_if
		(
			enemy.begin(),
			enemy.end(),
			[](Monster* monster)
			{ if (monster->isDead()) 
				{
					GM->kill++;
					GM->player->exp += monster->getExp();
					return true;
				}
			else false;
			}
		),
		enemy.end()
	);

	// 유닛끼리 충돌 처리
	collisionsBetweenUnits();

	for (auto& enemy : this->enemy)
		enemy->Update();
}

void MonsterManager::LateUpdate()
{
	Relocation();
	Pool();
}

void MonsterManager::Render()
{
	for (auto& enemy : this->enemy)
		enemy->Render();
}

void MonsterManager::collisionsBetweenUnits()
{
	for (auto& enemy : this->enemy)
	{
		// 플레이어와 몬스터 충돌
		if (enemy->getCollider()->Intersect(GM->player->getCollider()))
		{
			if (GM->player->getPlayerStatus() == PLAYER_STATUS::NORMAL)
				GM->player->actionsWhenDamaged(enemy->getDamage());

			Vector2 enemyDir = enemy->getCollider()->GetWorldPos() - GM->player->getCollider()->GetWorldPos();
			Vector2 OtherEnemyDir = GM->player->getCollider()->GetWorldPos() - enemy->getCollider()->GetWorldPos();

			enemyDir.Normalize();
			OtherEnemyDir.Normalize();

			enemy->getCollider()->MoveWorldPos(enemyDir * 200 * DELTA);
			GM->player->getCollider()->MoveWorldPos(OtherEnemyDir * 100 * DELTA);

		}

		// 몬스터와 몬스터 충돌
		for (auto& OtherEnemy : this->enemy)
		{
			// 충돌 몬스터가 자기 자신이면 넘김
			if (enemy == OtherEnemy) continue;

			// 몬스터가 다른 몬스터와 충돌하면 밀어냄
			if (enemy->getCollider()->Intersect(OtherEnemy->getCollider()))
			{
				Vector2 enemyDir = enemy->getCollider()->GetWorldPos() - OtherEnemy->getCollider()->GetWorldPos();
				Vector2 OtherEnemyDir = OtherEnemy->getCollider()->GetWorldPos() - enemy->getCollider()->GetWorldPos();

				enemyDir.Normalize();
				OtherEnemyDir.Normalize();

				enemy->getCollider()->MoveWorldPos(enemyDir * 500 * DELTA);
				OtherEnemy->getCollider()->MoveWorldPos(OtherEnemyDir * 500 * DELTA);
			}
		}
	}
}

void MonsterManager::AddEnemy(class Monster* monster)
{
	this->enemy.emplace_back(monster);
}

void MonsterManager::Relocation()
{

	for (auto& enemy : this->enemy)
	{
		if (enemy->getCollider()->Intersect(GM->player->getArea()))
		{
			continue;
		}

		float dirX = GM->player->getPos().x - enemy->getCollider()->GetWorldPos().x;
		float dirY = GM->player->getPos().y - enemy->getCollider()->GetWorldPos().y;

		float diffX = abs(dirX);
		float diffY = abs(dirY);

		dirX = dirX > 0 ? 1 : -1;
		dirY = dirY > 0 ? 1 : -1;

		Vector2 targetPos = GM->player->getPos();

		if (diffX > diffY)
		{
			enemy->getCollider()->SetWorldPos
			(
				targetPos
				+ RIGHT * dirX * app.GetHalfWidth() * RANDOM->Float(1.1f, 1.4f)
				+ UP * RANDOM->Int(-1, 1) * RANDOM->Float(50.0f, 300.0f)
			);
		}
		else if (diffX < diffY)
		{
			enemy->getCollider()->SetWorldPos
			(
				targetPos 
				+ RIGHT * RANDOM->Int(-1, 1) * RANDOM->Float(50.0f, 300.0f)
				+ UP * dirY * app.GetHalfHeight() * RANDOM->Float(1.1f, 1.4f)
			);
		}
		else
		{
			enemy->getCollider()->SetWorldPos
			(
				targetPos 
				+ (RIGHT * dirX * app.GetHalfWidth() * RANDOM->Float(1.1f, 1.4f)) 
				+ (UP * dirY * app.GetHalfHeight() * RANDOM->Float(1.1f, 1.4f))
			);
		}
	}
}

void MonsterManager::Pool()
{
	static float slimeSpawnTime = 0.0f;
	static float magaSlimeSpawnTime = 0.0f;
	static float kingSlimeSpawnTime = 0.0f;
	static float kingMegaSlimeSpawnTime = 0.0f;

	if (TIMER->GetTick(slimeSpawnTime, 3.0f))
	{
		Slime* slime = new Slime();
		slime->Init();
			
		GM->monster->AddEnemy(slime);
	}

	if (TIMER->GetWorldTime() > 7.0f)
	{
		if (TIMER->GetTick(magaSlimeSpawnTime, 4.0f))
		{
			MegaSlime* megaSlime = new MegaSlime();
			megaSlime->Init();

			GM->monster->AddEnemy(megaSlime);
		}
	}

	if (TIMER->GetWorldTime() > 15.0f)
	{
		if (TIMER->GetTick(kingSlimeSpawnTime, 5.0f))
		{
			KingSlime* kingSlime = new KingSlime();
			kingSlime->Init();

			GM->monster->AddEnemy(kingSlime);
		}
	}

	if (TIMER->GetWorldTime() > 20.0f)
	{
		if (TIMER->GetTick(kingMegaSlimeSpawnTime, 5.0f))
		{
			KingMegaSlime* kingMegaSlime = new KingMegaSlime();
			kingMegaSlime->Init();

			GM->monster->AddEnemy(kingMegaSlime);
		}
	}
}
