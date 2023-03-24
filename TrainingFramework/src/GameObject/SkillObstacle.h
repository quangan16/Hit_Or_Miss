#pragma once
#include "CMath.h"


class SkillObstacle
{
private:
	Vector2 m_spawnPosition;
	Vector2 m_endPosition;
	GLfloat m_speed;
public:
	SkillObstacle();
	SkillObstacle(Vector2 spawnPosition, Vector2 endPosition, GLfloat speed);
	void SetSpawnPosition(Vector2 spawnPosition);
	void SetEndPosition(Vector2 endPosition);
	void SetSpeed(GLfloat speed);
	
};

