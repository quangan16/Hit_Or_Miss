#include "ObstacleSpawner.h"

#include "GameStates/GSPlay.h"



ObstacleSpawner::~ObstacleSpawner(){};


void ObstacleSpawner::UpdateSpawn(GLfloat deltaTime) {
    m_intervalTime += deltaTime;
    int screenWidth = Globals::screenWidth;
	int screenHeight = Globals::screenHeight;

    // Generate random position off-screen
    int x = rand() % screenWidth;
    int y = rand() % screenHeight;
    if (rand() % 2 == 0) {
        x -= screenWidth;
    }
    else {
        x += screenWidth;
    }
    if (rand() % 2 == 0) {
        y -= screenHeight;
    }
    else {
        y += screenHeight;
    }

    
   if(m_intervalTime>1)
   {
       this->SetSpawnPosition(Vector2(x, y));
       m_intervalTime = 0;
   }

    // Spawn enemy at generated position with chosen direction
    
    /* add enemy to game world */
}

void ObstacleSpawner::ShootSkill()
{



}

void ObstacleSpawner::SetSpawnPosition(Vector2 spawnPosition)
{
	this->m_spawnPosition.x = spawnPosition.x;
	this->m_spawnPosition.y = spawnPosition.y;
}

Vector2 ObstacleSpawner::GetSpawnPosition()
{
	return m_spawnPosition;
}


//void ObstacleSpawner::EnemySpawn(GLfloat deltaTime) {
//	std::cout << "pool" << enemies.size() << "\n";
//	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
//	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
//	auto texture = ResourceManagers::GetInstance()->GetTexture("arrow-up.tga");
//	spawnTime += deltaTime;
//
//	if (spawnTime > 1) {
//		m_enemy = std::make_shared<Enemy>(model, shader, texture);
//		m_enemy->SetRandomPosition();
//		m_enemy->SetEnemyDirection(atan2(m_player->GetPlayerPosition().y - m_enemy->GetEnemyPosition().y, m_player->GetPlayerPosition().x - m_enemy->GetEnemyPosition().x));
//		m_enemy->SetSize(100, 100);
//
//		bool isActiveAll = true;
//		for (int i = 0; i < enemies.size(); i++) {
//			if (!activeStatus[i]) {
//				isActiveAll = false;
//				enemies[i] = m_enemy;
//				activeStatus[i] = true;
//				break;
//			}
//		}
//		if (isActiveAll) {
//			enemies.push_back(m_enemy);
//			activeStatus.push_back(true);
//		}
//
//		spawnTime = 0;
//	}
//	for (int i = 0; i < enemies.size(); i++) {
//
//		if (enemies[i]->GetEnemyPosition().x < 0 || enemies[i]->GetEnemyPosition().x >(float)Globals::screenWidth || enemies[i]->GetEnemyPosition().y < 0 || enemies[i]->GetEnemyPosition().y >(float)Globals::screenHeight) {
//			activeStatus[i] = false;
//		}
//		else {
//			enemies[i]->MoveTowardPlayer(m_player->GetPlayerPosition(), enemies[i]->GetEnemySpeed(), enemies[i]->GetEnemyPosition(), deltaTime, enemies[i]->GetEnemyDirection());
//		}
//	}
//}




