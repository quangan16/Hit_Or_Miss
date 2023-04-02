#pragma once
#include "vector"
#include "memory"
#include "Enemy.h"
#include <queue>

class EnemyPool
{
public:
    EnemyPool(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint poolSize);

    std::shared_ptr<Enemy> GetEnemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);

    void ReturnEnemy(std::shared_ptr<Enemy> enemy);

    GLint GetEnemyPoolSize();

private:
    std::vector<std::shared_ptr<Enemy>> m_enemyPool;
    std::vector<bool> m_available;
};