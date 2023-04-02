#pragma once
#include "GameConfig.h"
class CircleCollider2D {
public:
    // Constructor
    CircleCollider2D(GLfloat x, float y, float radius) {
        m_x = x;
        m_y = y;
        m_radius = radius;
    }

    // Check collision with another circle collider
    bool CheckCollision(const CircleCollider2D& otherCircle) const {
        float distance = sqrt((m_x - otherCircle.m_x) * (m_x - otherCircle.m_x) + (m_y - otherCircle.m_y) * (m_y - otherCircle.m_y));
        return distance <= m_radius + otherCircle.m_radius;
    }

private:
    float m_x, m_y;
    float m_radius;
};

