#pragma once
#include "BoxCollider2D.h"
#include "CircleCollider2D.h"
#include "CMath.h"
#include "Sprite2D.h"
#include "SpriteAnimation.h"
#include "ResourceManagers.h"
#include "GameConfig.h"

typedef enum EFFECT { NORMAL, FREEZE, BURN, SLOW } Effect;
class SkillObstacle
{
private:
	Vector2 m_obstacleDirection;
	Vector2 m_obstacleCurrentPosition;
	Vector2 m_obstacleStartPosition;
	Vector2 m_obstacleTargetPosition;
	GLfloat m_obstacleSpeed;
	Effect m_obstacleEffect;
public:
	SkillObstacle() : m_obstacleStartPosition(0.0f, 0.0f), m_obstacleCurrentPosition(0.0f, 0.0f), m_obstacleDirection(0.0f, 0.0f), m_obstacleSpeed(500.0f), m_obstacleEffect(NORMAL){};
	SkillObstacle(Vector2 startPosition, Vector2 targetPosition, GLfloat speed, Effect effect);

	void SetTargetDirection(Vector2 startPos, Vector2 target);
	void FlyToTarget(Vector2 startPos, Vector2 target, GLfloat deltaTime);

	Vector2 GetCurrentPosition();
	Vector2 GetStartPosition();
	void GetObstacleSpeed(GLfloat speed);
	void GetObstacleEffect(Effect effect);
	
	
	void SetCurrentPosition(Vector2 curentPosition);
	void SetStartPosition(Vector2 startPosition);
	void SetObstacleSpeed(GLfloat speed);
	void SetObstacleEffect(Effect effect);
	void SetObstacleRotation(std::shared_ptr<SpriteAnimation>& m_animationSprite, Vector2 &start, Vector2 &target);




	void HandleObstacleAnimation(std::shared_ptr<SpriteAnimation>& m_animationSprite, std::list<std::shared_ptr<SpriteAnimation>>& m_listAnimation);
};

