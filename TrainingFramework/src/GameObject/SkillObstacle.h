#pragma once
#include "CMath.h"

typedef enum EFFECT {NORMAL, FREEZE, BURN, SLOW} Effect;
class SkillObstacle
{
private:
	Vector2 m_spawnPosition;
	Vector2 m_endPosition;
	GLfloat m_speed;
	Effect m_effect;
public:
	SkillObstacle();
	SkillObstacle(Vector2 spawnPosition, Vector2 endPosition, GLfloat speed);
	void SetSpawnPosition(Vector2 spawnPosition);
	void SetEndPosition(Vector2 endPosition);
	void SetSpeed(GLfloat speed);
	void SetEffect(Effect effect);
	
};

