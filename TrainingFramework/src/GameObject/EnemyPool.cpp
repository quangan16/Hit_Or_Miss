#include "EnemyPool.h"
#include "Enemy.h"

EnemyPool::EnemyPool(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint poolSize)
{
    for (int i = 0; i < poolSize; i++) {
        auto enemy = std::make_shared<Enemy>(model, shader, texture);
        enemy->SetActive(false);
        m_enemyPool.push_back(enemy);
        m_available.push_back(true);
    }
}

std::shared_ptr<Enemy> EnemyPool::GetEnemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
{
    for (int i = 0; i < m_enemyPool.size(); i++) {
        if (m_available[i]) {
            m_available[i] = false;
            return m_enemyPool[i];
        }
    }

    auto enemy = std::make_shared<Enemy>(model, shader, texture);
    m_enemyPool.push_back(enemy);
    m_available.push_back(false);
    return enemy;
}

void EnemyPool::ReturnEnemy(std::shared_ptr<Enemy> enemy) {
    for (int i = 0; i < m_enemyPool.size(); i++)
    {
        if (enemy == m_enemyPool[i] && !m_available[i])
        {
            m_available[i] = true;
            enemy->SetActive(false);
            return;
        }
    }
}

GLint EnemyPool::GetEnemyPoolSize() {
    return m_enemyPool.size();
}