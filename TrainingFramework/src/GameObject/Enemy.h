#pragma once
#include "Sprite2D.h"
#include "BoxCollider2D.h"
class Enemy : public Sprite2D, public BoxCollider2D
{
protected:
	GLfloat m_enemySpeed;
	GLfloat m_enemyDirection;
public:
	Enemy() : Sprite2D(), BoxCollider2D(), m_enemySpeed(0), m_enemyDirection(0) {}
	Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);

	//~Enemy();
	void Enemy::MoveTowardPlayer(Vector2 playerPosition, GLfloat enemySpeed, Vector2 enemyPostion, GLfloat deltaTime, GLfloat direction);

	GLfloat Enemy::GetEnemySpeed();
	void Enemy::SetEnemySpeed(GLfloat speed);

	GLfloat Enemy::GetEnemyDirection();
	void Enemy::SetEnemyDirection(GLfloat direct);

	void SetEnemyPosition(GLfloat x, GLfloat y) { Set2DPosition(x, y); }
	Vector2 GetEnemyPosition() { return Get2DPosition(); }

	void SetRandomPosition();

	void SetEnemyRotation(Vector3 rotation) { SetRotation(rotation); }

	void Draw();

};