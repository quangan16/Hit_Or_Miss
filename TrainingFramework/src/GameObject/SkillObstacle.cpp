#include "SkillObstacle.h"
#include "Player.h"
#include "esUtil.h"
#include "SpriteAnimation.h"

SkillObstacle::SkillObstacle()
{
}

SkillObstacle::SkillObstacle(Vector2 startPosition, GLfloat speed, Effect effect)
{
	
	this->m_obstacleStartPosition = startPosition;
	this->m_obstacleCurrentPosition = startPosition;
	this->m_obstacleSpeed = speed;
	this->m_obstacleEffect = effect;
}



Vector2 SkillObstacle::GetCurrentPosition()
{
	return this->m_obstacleCurrentPosition;
}

Vector2 SkillObstacle::GetStartPosition()
{
	return this->m_obstacleStartPosition;
}

void SkillObstacle::SetCurrentPosition(Vector2 currentPosition)
{
	this->m_obstacleCurrentPosition = currentPosition;
}

void SkillObstacle::SetStartPosition(Vector2 spawnPosition)
{
	this->m_obstacleStartPosition = spawnPosition;
}


void SkillObstacle::SetObstacleSpeed(GLfloat speed)
{
	this->m_obstacleSpeed = speed;
}

void SkillObstacle::SetObstacleEffect(Effect effect)
{
	this->m_obstacleEffect = effect;
}



void SkillObstacle::FlyToPlayer(Vector2 startPos, Vector2 target, GLfloat deltaTime)
{
	Vector2 direction = target - startPos;
	direction.Normalize();
	this->m_obstacleCurrentPosition += direction * this->m_obstacleSpeed * deltaTime;
}

void SkillObstacle::HandleObstacleAnimation(std::shared_ptr<SpriteAnimation>& m_animationSprite, std::list<std::shared_ptr<SpriteAnimation>>& m_listAnimation)
{
	
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Warrior/Down/WarriorDownIdle.tga ");;
	m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 5, 1, 0, 0.1f);
	m_listAnimation.clear();
	m_listAnimation.push_back(m_animationSprite);
}