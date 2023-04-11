#pragma once
#include "CMath.h"
#include "Enemy.h"
#include "GameConfig.h"
#include "SkillObstacle.h"
#include "ObjectPool.h"
#include "Player.h"

class ObstacleSpawner
{
	
private:
	
	GLfloat m_intervalTime;
	
	Vector2 m_spawnPosition;
	std::vector<std::shared_ptr<Enemy>> enemies;
public:
	GLfloat m_counter;
	std::shared_ptr<SkillObstacle> m_obstacle;
	ObstacleSpawner() : m_spawnPosition{ 0.f, 0.f }, m_counter{ 0.f }{};
	ObstacleSpawner(Vector2 m_spawnPosition) :m_spawnPosition{ 0.f, 0.f }, m_counter{ 0.f }{};
	~ObstacleSpawner();
    void UpdateSpawn(std::shared_ptr<SpriteAnimation> &obstacleAnimationSprite, std::list<std::shared_ptr<SpriteAnimation>> &obstacleAnimationList, std::shared_ptr<Player> &player, GLfloat intervalTime, GLfloat deltaTime, Vector2 &randomPos, ObjectPool<std::shared_ptr<SkillObstacle>>** objectPool, std::shared_ptr<SkillObstacle> &obstacle);
	void ShootSkill();

	Vector2 GetSpawnPosition();
	void SetSpawnPosition(Vector2 spawnPosition);
	void EnemySpawn(GLfloat deltaTime);
};

