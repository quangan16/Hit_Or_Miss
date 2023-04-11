#pragma once
#include "CMath.h"
#include "Enemy.h"
#include "GameConfig.h"
#include "SkillObstacle.h"
#include "ObjectPool.h"

class ObstacleSpawner
{
private:
	GLfloat m_intervalTime;
	Vector2 m_spawnPosition;
	std::vector<std::shared_ptr<Enemy>> enemies;
public:
	ObstacleSpawner() : m_spawnPosition{ 0.f, 0.f }, m_intervalTime{ 0.f }{};
	ObstacleSpawner(Vector2 m_spawnPosition) :m_spawnPosition{ 0.f, 0.f }, m_intervalTime{ 0.f }{};
	~ObstacleSpawner();
	void UpdateSpawn(GLfloat deltaTime);
	void ShootSkill();

	Vector2 GetSpawnPosition();
	void SetSpawnPosition(Vector2 spawnPosition);
	void EnemySpawn(GLfloat deltaTime);
};

