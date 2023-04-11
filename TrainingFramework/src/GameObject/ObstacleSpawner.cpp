#include "ObstacleSpawner.h"

#include "GameStates/GSPlay.h"



ObstacleSpawner::~ObstacleSpawner(){};

void ObstacleSpawner::UpdateSpawn(std::shared_ptr<SpriteAnimation> &obstacleAnimationSprite, std::list<std::shared_ptr<SpriteAnimation>> &obstacleAnimationList, std::shared_ptr<Player> &player, GLfloat intervalTime, GLfloat deltaTime, Vector2 &randomPos, ObjectPool<std::shared_ptr<SkillObstacle>>** objectPool, std::shared_ptr<SkillObstacle> &obstacle)
{

	m_counter += deltaTime;
	// Generate random position off-screen
	int x, y;
	int side = std::rand() % 4; // choose a random side of the offscreen area
	switch (side)
	{
	case 0: // top side
		x = std::rand() % (Globals::screenWidth - 50) + 50;
		y = -std::rand() % Globals::screenWidth;
		break;
	case 1: // right side
		x = Globals::screenWidth + std::rand() % 50;
		y = std::rand() % (Globals::screenHeight - 50) + 50;
		break;
	case 2: // bottom side
		x = std::rand() % (Globals::screenWidth - 50) + 50;
		y = Globals::screenHeight + std::rand() % 50;
		break;
	case 3: // left side
		x = -std::rand() % 50;
		y = std::rand() % (Globals::screenHeight - 50) + 50;
		break;
	}

	// Print the random position


	if (m_counter >= intervalTime)
	{
		randomPos = player->GetPlayerRandomPosCircle(150.0f);

		this->SetSpawnPosition(Vector2(x, y));
		obstacle = (*objectPool)->acquireObject();
		obstacle->SetObstacleSpeed(400);
		obstacle->SetStartPosition(this->GetSpawnPosition()); 
		obstacle->SetCurrentPosition(obstacle->GetStartPosition());
		
		
		//std::cout << "new!";
		m_counter = 0.f;
		// Spawn enemy at generated position with chosen direction
		(*objectPool)->getAvailableObjectsSize();
		/* add enemy to game world */
		
	}
	if (obstacle->GetCurrentPosition().x < -60.f || obstacle->GetCurrentPosition().x >(float)Globals::screenWidth + 60.f || obstacle->GetCurrentPosition().y < -60.f || obstacle->GetCurrentPosition().y >(float)Globals::screenHeight + 60.f) {

		(*objectPool)->releaseObject(obstacle);
		std::cout << "take back";

	}
	else {
		obstacle->SetObstacleRotation(obstacleAnimationSprite, obstacle->GetStartPosition(), randomPos);
		obstacle->FlyToTarget(obstacle->GetStartPosition(), randomPos, deltaTime);
		//std::cout << randomPos.x << " " << randomPos.x << std::endl;
		obstacleAnimationSprite->Set2DPosition(obstacle->GetCurrentPosition().x, obstacle->GetCurrentPosition().y);

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




