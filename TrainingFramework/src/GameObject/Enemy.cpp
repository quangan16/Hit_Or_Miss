#include "Enemy.h"
#include "Math.h"

Enemy::Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture), m_enemySpeed(500), m_enemyDirection(0), m_isActive(false)
{
	Init();
}

GLfloat Enemy::GetEnemySpeed() {
	return m_enemySpeed;
}

void Enemy::SetEnemySpeed(GLfloat speed) {
	m_enemySpeed = speed;
}

GLfloat Enemy::GetEnemyDirection() {
	return m_enemyDirection;
}

void Enemy::SetEnemyDirection(GLfloat direct) {
	m_enemyDirection = direct;
}

void Enemy::SetActive(bool isActive) {
	m_isActive = isActive;
}

bool Enemy::IsActive() {
	return m_isActive;
}

void Enemy::MoveTowardPlayer(Vector2 playerPosition, GLfloat enemySpeed, Vector2 enemyPosition, GLfloat deltaTime, GLfloat direction) {
	enemyPosition += Vector2(cos(direction), sin(direction)) * enemySpeed * deltaTime;
	SetEnemyPosition(enemyPosition.x, enemyPosition.y);
}

void Enemy::Draw()
{
	Sprite2D::Draw();
}