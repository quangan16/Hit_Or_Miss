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
<<<<<<< HEAD
	
	Vector2 m_spawnPosition;
	std::vector<std::shared_ptr<Enemy>> enemies;
public:
	GLfloat m_counter;
=======
	GLfloat m_counter;
	Vector2 m_spawnPosition;
	std::vector<std::shared_ptr<Enemy>> enemies;
public:
>>>>>>> parent of 9298f43 (add more types of enemies, implement a mechanism to increase the game's difficulty over time)
	std::shared_ptr<SkillObstacle> m_obstacle;
	ObstacleSpawner() : m_spawnPosition{ 0.f, 0.f }, m_counter{ 0.f }{};
	ObstacleSpawner(Vector2 m_spawnPosition) :m_spawnPosition{ 0.f, 0.f }, m_counter{ 0.f }{};
	~ObstacleSpawner();
<<<<<<< HEAD
    void UpdateSpawn(std::shared_ptr<SpriteAnimation> &obstacleAnimationSprite, std::list<std::shared_ptr<SpriteAnimation>> &obstacleAnimationList, std::shared_ptr<Player> &player, GLfloat intervalTime, GLfloat deltaTime, Vector2 &randomPos, ObjectPool<std::shared_ptr<SkillObstacle>>** objectPool, std::shared_ptr<SkillObstacle> &obstacle);
=======
    void UpdateSpawn(std::shared_ptr<Player> object,GLfloat intervalTime, GLfloat deltaTime, std::shared_ptr<SpriteAnimation>& m_animationSprite, std::list<std::shared_ptr<SpriteAnimation>>& m_listAnimation);
>>>>>>> parent of 9298f43 (add more types of enemies, implement a mechanism to increase the game's difficulty over time)
	void ShootSkill();

	Vector2 GetSpawnPosition();
	void SetSpawnPosition(Vector2 spawnPosition);
	void EnemySpawn(GLfloat deltaTime);
};

