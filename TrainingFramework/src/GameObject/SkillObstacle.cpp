#include "SkillObstacle.h"
#include "Player.h"
#include "esUtil.h"




SkillObstacle::SkillObstacle(Vector2 startPosition, Vector2 targetPosition, GLfloat speed, Effect effect)
{
	
	this->m_obstacleStartPosition = startPosition;
	this->m_obstacleCurrentPosition = startPosition;
	this->m_obstacleSpeed = speed;
	this->m_obstacleEffect = effect;
	this->m_obstacleTargetPosition = targetPosition;
}



void SkillObstacle::SetTargetDirection(Vector2 startPos, Vector2 target)
{
	m_obstacleDirection = target - startPos;
	m_obstacleDirection.Normalize() ;

}


void SkillObstacle::SetObstacleRotation(std::shared_ptr<SpriteAnimation>& m_animationSprite, Vector2 startPos, Vector2 target)
{
	
	m_animationSprite->SetRotation(Vector3(0.f, 0.f, atan2(m_obstacleDirection.y, m_obstacleDirection.x) - M_PI / 2));
}



void SkillObstacle::FlyToTarget(Vector2 startPos, Vector2 target, GLfloat deltaTime)
{
	
	SetTargetDirection( startPos,  target);
	this->m_obstacleCurrentPosition += m_obstacleDirection * this->m_obstacleSpeed * deltaTime;
	//std::cout << m_obstacleStartPosition.x;
}

void SkillObstacle::HandleObstacleAnimation(std::shared_ptr<SpriteAnimation>& m_animationSprite, std::list<std::shared_ptr<SpriteAnimation>>& m_listAnimation)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Effects\\Rarity Effects\\Magic effect.tga");
	m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 9, 1, 0, 0.05f);
	m_animationSprite->Set2DPosition(this->m_obstacleCurrentPosition.x, this->m_obstacleCurrentPosition.y);
	//m_animationSprite->SetRotation(Vector3(0.f, 0.f, atan2(m_obstacleDirection.y, m_obstacleDirection.x) - M_PI / 2));
	m_animationSprite->SetSize(50, 120);
	m_listAnimation.clear();
	m_listAnimation.push_back(m_animationSprite);
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

