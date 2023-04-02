#include "Enemy.h"
#include "Math.h"

Enemy::Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
    : Sprite2D(model, shader, texture), m_enemySpeed(500), m_enemyDirection(0)
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

void Enemy::SetRandomPosition() {
    int x, y;
    int side = rand() % 4;
    switch (side) {
    case 0:  // upper
        x = (float)rand() / RAND_MAX * (float)Globals::screenWidth;
        y = (float)Globals::screenHeight;
        SetEnemyPosition(x, y);
        break;
    case 1:  // right
        x = (float)Globals::screenWidth;
        y = (float)rand() / RAND_MAX * (float)Globals::screenHeight;
        SetEnemyPosition(x, y);
        break;
    case 2:  // down
        x = (float)rand() / RAND_MAX * (float)Globals::screenHeight;
        y = 0;
        SetEnemyPosition(x, y);
        break;
    case 3:  // left
        x = 0;
        y = (float)rand() / RAND_MAX * (float)Globals::screenHeight;
        SetEnemyPosition(x, y);
        break;
    }
}

void Enemy::MoveTowardPlayer(Vector2 playerPosition, GLfloat enemySpeed, Vector2 enemyPosition, GLfloat deltaTime, GLfloat direction) {
    enemyPosition += Vector2(cos(direction), sin(direction)) * enemySpeed * deltaTime;
    SetEnemyPosition(enemyPosition.x, enemyPosition.y);
}

void Enemy::Draw()
{
    Sprite2D::Draw();
}