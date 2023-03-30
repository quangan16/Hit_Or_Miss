#include "SkillObstacle.h"

SkillObstacle::SkillObstacle()
{
}

SkillObstacle::SkillObstacle(Vector2 spawnPosition, GLfloat speed, Effect effect)
{
	this->m_obstacleCurrentPosition = spawnPosition;
	this->m_obstacleSpeed = speed;
	this->m_obstacleEffect = effect;
}

void SkillObstacle::SetCurrentPosition(Vector2 spawnPosition)
{
	this->m_obstacleCurrentPosition = spawnPosition;
}


void SkillObstacle::SetObstacleSpeed(GLfloat speed)
{
	this->m_obstacleSpeed = speed;
}

void SkillObstacle::SetObstacleEffect(Effect effect)
{
	this->m_obstacleEffect = effect;
}

Vector2 SkillObstacle::GetCurrentPosition()
{
	return this->m_obstacleCurrentPosition;
}
