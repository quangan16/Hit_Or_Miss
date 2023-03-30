#pragma once
#include "CMath.h"
#include "Sprite2D.h"

typedef enum EFFECT { NORMAL, FREEZE, BURN, SLOW } Effect;
class SkillObstacle:Sprite2D
{
private:
	Vector2 m_obstacleCurrentPosition;
	GLfloat m_obstacleSpeed;
	Effect m_obstacleEffect;
public:
	SkillObstacle();
	SkillObstacle(Vector2 currentPosition, GLfloat speed, Effect effect);

	void SetCurrentPosition(Vector2 curentPosition);
	void SetObstacleSpeed(GLfloat speed);
	void SetObstacleEffect(Effect effect);

	Vector2 GetCurrentPosition();
	
};

