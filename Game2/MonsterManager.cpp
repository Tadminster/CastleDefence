#include "stdafx.h"
#include "Monster.h"
#include "Slime.h"
#include "MonsterManager.h"

void MonsterManager::Init()
{
	Slime* slime[10];
	for (int i = 0; i < 10; i++)
	{
		slime[i] = new Slime();
		slime[i]->Init();
		MONSTER->AddEnemy(slime[i]);
	}
}

void MonsterManager::Release()
{
}

void MonsterManager::Update()
{
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

void MonsterManager::AddEnemy(class Monster* monster)
{
	this->enemy.emplace_back(monster);
}

void MonsterManager::Relocation()
{

	for (auto& enemy : this->enemy)
	{
		
		//ImGui::Text("bg[%i] pos_X = %f\n", i, col_bg->GetWorldPos().x);
		//ImGui::Text("bg[%i] pos_Y = %f\n", i, col_bg->GetWorldPos().y);
		if (enemy->getCollider()->Intersect(GM->player->getArea()))
		{
			//i++;
			continue;

		}

		float dirX = GM->player->getPos().x - enemy->getCollider()->GetWorldPos().x;
		float dirY = GM->player->getPos().y - enemy->getCollider()->GetWorldPos().y;
		//ImGui::Text("bg[%i] dir_X = %i\n", i, dirX);
		//ImGui::Text("bg[%i] dir_Y = %i\n", i, dirY);

		float diffX = abs(dirX);
		float diffY = abs(dirY);

		dirX = dirX > 0 ? 1 : -1;
		dirY = dirY > 0 ? 1 : -1;

		//ImGui::Text("bg[%i] diff_X = %f\n", i, diffX);
		//ImGui::Text("bg[%i] diff_Y = %f\n", i, diffY);
		//ImGui::Text("bg[%i] dir_X = %i\n", i, dirX);
		//ImGui::Text("bg[%i] dir_Y = %i\n\n", i, dirY);
		//i++;
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
	static float spawnTime = 0.0f;
	if (TIMER->GetTick(spawnTime, 3.0f))
	{
		Slime* slime = new Slime();
		slime->Init();
			
		MONSTER->AddEnemy(slime);
	}
}
