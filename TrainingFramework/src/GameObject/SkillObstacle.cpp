#include "SkillObstacle.h"

SkillObstacle::SkillObstacle() {

}

SkillObstacle::SkillObstacle(Vector2 spawnPosition, Vector2 endPosition, GLfloat speed) {
	this->m_spawnPosition = spawnPosition;
	this->m_endPosition = endPosition;
	this->m_speed = speed;
}

void SkillObstacle::SetSpawnPosition(Vector2 spawnPosition)
{
	m_spawnPosition = spawnPosition;
}


void SkillObstacle::SetEndPosition(Vector2 endPosition) {
	m_endPosition = endPosition;
}
void SkillObstacle::SetSpeed(GLfloat speed){
	m_speed = speed;
}
	



