#pragma once
#include "CMath.h"
#include "Sprite2D.h"
#include "SpriteAnimation.h"
#include "ResourceManagers.h"
#include "GameConfig.h"

typedef enum EFFECT { NORMAL, FREEZE, BURN, SLOW } Effect;
class SkillObstacle:Sprite2D
{
private:
	Vector2 m_obstacleCurrentPosition;
	Vector2 m_obstacleStartPosition;
	GLfloat m_obstacleSpeed;
	Effect m_obstacleEffect;
public:
	SkillObstacle();
	SkillObstacle(Vector2 startPosition, GLfloat speed, Effect effect);

	Vector2 GetCurrentPosition();
	Vector2 GetStartPosition();

	void FlyToPlayer(Vector2 startPos, Vector2 direction, GLfloat deltaTime);
	void SetCurrentPosition(Vector2 curentPosition);
	void SetStartPosition(Vector2 startPosition);
	void SetObstacleSpeed(GLfloat speed);
	void SetObstacleEffect(Effect effect);

	void HandleObstacleAnimation(std::shared_ptr<SpriteAnimation>& m_animationSprite, std::list<std::shared_ptr<SpriteAnimation>>& m_listAnimation);
};

