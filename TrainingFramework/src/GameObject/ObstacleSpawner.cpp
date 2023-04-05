#include "ObstacleSpawner.h"

#include "GameStates/GSPlay.h"



ObstacleSpawner::~ObstacleSpawner(){};
ObjectPool<std::shared_ptr<SkillObstacle>>* objectPool = ObjectPool<std::shared_ptr<SkillObstacle>>::getInstance();

void ObstacleSpawner::UpdateSpawn(std::shared_ptr<Player> player, GLfloat intervalTime, GLfloat deltaTime, std::shared_ptr<SpriteAnimation>& m_animationSprite, std::list<std::shared_ptr<SpriteAnimation>>& m_listAnimation) {
    m_counter += deltaTime;
    
    
    // Generate random position off-screen
    int x = rand() % Globals::screenWidth;
    int y = rand() % Globals::screenHeight;
    if (rand() % 2 == 0) {
        x -= Globals::screenWidth;
    }
    else {
        x += Globals::screenWidth;
    }
    if (rand() % 2 == 0) {
        y -= Globals::screenHeight;
    }
    else {
        y += Globals::screenHeight;
    }


    if (m_counter > intervalTime)
    {
		player->GetPlayerRandomPosCircle(300);
        this->SetSpawnPosition(Vector2(x, y));

        m_obstacle = objectPool->acquireObject();

        if (m_obstacle->GetCurrentPosition().x < 0 || m_obstacle->GetCurrentPosition().x >(float)Globals::screenWidth || m_obstacle->GetCurrentPosition().y < 0 || m_obstacle->GetCurrentPosition().y >(float)Globals::screenHeight) {
            objectPool->releaseObject(m_obstacle);
            std::cout << "Released";
        }
        else {
            m_obstacle->FlyToTarget(m_obstacle->GetStartPosition(), player->GetPlayerRandomPosCircle(50.0f), deltaTime);
            std::cout << m_obstacle->GetCurrentPosition().x;
           
        }
       
        m_counter = 0.f;
        // Spawn enemy at generated position with chosen direction
        
        /* add enemy to game world */
    }
    
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




