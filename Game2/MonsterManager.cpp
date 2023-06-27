#include "stdafx.h"
#include "Projectile.h"
#include "Monster.h"
#include "Slime.h"
#include "KingSlime.h"
#include "MegaSlime.h"
#include "KingMegaSlime.h"
#include "SkeletonWarrior.h"
#include "SkeletoneMage.h"
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

	SkeletoneMage* skelMage = new SkeletoneMage();
	skelMage->Init();
	GM->monster->AddEnemy(skelMage);
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

	//탄이 플레이어와 충돌하면
	//projectiles.erase(
	//std::remove_if
	//(
	//	projectiles.begin(),
	//	projectiles.end(),
	//	[](unique_ptr<Projectile>& pr) { return pr->hasCollideWithMonster(); }
	//),
	//projectiles.end()
	//);

	// 적 업데이트
	for (auto& enemy : this->enemy)
		enemy->Update();
	// 탄 업데이트
	for (auto& projectiles : projectiles)
		projectiles->Update();
}

void MonsterManager::LateUpdate()
{
	Relocation();
	Pool();
}

void MonsterManager::Render()
{
	// 적 랜더
	for (auto& enemy : this->enemy)
		enemy->Render();
	// 탄 랜더
	for (auto& projectiles : projectiles)
		projectiles->Render();
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

				// 서로 (미니언||엘리트) 라면
				if ((enemy->getType() == MONSTER_TYPE::MINION || enemy->getType() == MONSTER_TYPE::ELITE) &&
					(OtherEnemy->getType() == MONSTER_TYPE::MINION || OtherEnemy->getType() == MONSTER_TYPE::ELITE))
				{
					enemy->getCollider()->MoveWorldPos(enemyDir * 500 * DELTA);
					OtherEnemy->getCollider()->MoveWorldPos(OtherEnemyDir * 500 * DELTA);
				}
				// A가 (미니언||엘리트)이고, B가 (챔피언||보스) 라면
				else if ((enemy->getType() == MONSTER_TYPE::MINION || enemy->getType() == MONSTER_TYPE::ELITE) &&
					(OtherEnemy->getType() == MONSTER_TYPE::CHAMPION || OtherEnemy->getType() == MONSTER_TYPE::BOSS))
				{
					enemy->getCollider()->MoveWorldPos(enemyDir * 1000 * DELTA);
					OtherEnemy->getCollider()->MoveWorldPos(OtherEnemyDir * 50 * DELTA);
				}
				// A가 (챔피언||보스)이고, B가 (미니언||엘리트) 라면
				else if ((enemy->getType() == MONSTER_TYPE::CHAMPION || enemy->getType() == MONSTER_TYPE::BOSS) &&
					(OtherEnemy->getType() == MONSTER_TYPE::MINION || OtherEnemy->getType() == MONSTER_TYPE::ELITE))
				{
					enemy->getCollider()->MoveWorldPos(enemyDir * 50 * DELTA);
					OtherEnemy->getCollider()->MoveWorldPos(OtherEnemyDir * 1000 * DELTA);
				}
				// 서로 (챔피언||보스) 라면
				else if ((enemy->getType() == MONSTER_TYPE::CHAMPION || enemy->getType() == MONSTER_TYPE::BOSS) &&
						(OtherEnemy->getType() == MONSTER_TYPE::CHAMPION || OtherEnemy->getType() == MONSTER_TYPE::BOSS))
				{
					enemy->getCollider()->MoveWorldPos(enemyDir * 500 * DELTA);
					OtherEnemy->getCollider()->MoveWorldPos(OtherEnemyDir * 500 * DELTA);
				}

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
	static float SkeletonWarriorSpawnTime = 0.0f;
	

	if (TIMER->GetTick(slimeSpawnTime, 2.0f))
	{
		Slime* slime = new Slime();
		slime->Init();
			
		GM->monster->AddEnemy(slime);
	}

	if (TIMER->GetWorldTime() > 7.0f)
	{
		if (TIMER->GetTick(magaSlimeSpawnTime, 3.0f))
		{
			MegaSlime* megaSlime = new MegaSlime();
			megaSlime->Init();

			GM->monster->AddEnemy(megaSlime);
		}
	}

	if (TIMER->GetWorldTime() > 20.0f)
	{
		if (TIMER->GetTick(kingSlimeSpawnTime, 4.0f))
		{
			KingSlime* kingSlime = new KingSlime();
			kingSlime->Init();

			GM->monster->AddEnemy(kingSlime);
		}
	}

	if (TIMER->GetWorldTime() > 35.0f)
	{
		if (TIMER->GetTick(kingMegaSlimeSpawnTime, 5.0f))
		{
			KingMegaSlime* kingMegaSlime = new KingMegaSlime();
			kingMegaSlime->Init();

			GM->monster->AddEnemy(kingMegaSlime);
		}
	}

	//if (TIMER->GetWorldTime() > 50.0f)

	if (TIMER->GetWorldTime() > 50.0f)
	{
		if (TIMER->GetTick(SkeletonWarriorSpawnTime, 4.0f))
		{
			SkeletonWarrior* skeletonWarrior = new SkeletonWarrior();
			skeletonWarrior->Init();

			GM->monster->AddEnemy(skeletonWarrior);
		}
	}
	else if (TIMER->GetWorldTime() > 5.0f)
	{
		if (TIMER->GetTick(SkeletonWarriorSpawnTime, 10.0f))
		{
			SkeletonWarrior* skeletonWarrior = new SkeletonWarrior();
			skeletonWarrior->Init();

			GM->monster->AddEnemy(skeletonWarrior);
		}
	} 
}
