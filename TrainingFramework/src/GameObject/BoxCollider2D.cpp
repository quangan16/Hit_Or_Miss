#include "BoxCollider2D.h"


BoxCollider2D::BoxCollider2D()
{
	
}

BoxCollider2D::BoxCollider2D(Vector2 objectPos, float width, float height) {
    this->m_colliderPosition = objectPos;
    m_width = width;
    m_height = height;
}


bool BoxCollider2D::CheckCollision(const BoxCollider2D& otherBox) {
    if (this->m_colliderPosition.x + m_width/2 < otherBox.m_colliderPosition.x- m_width / 2 || this->m_colliderPosition.x > otherBox.m_colliderPosition.x + otherBox.m_width/2) return false;
    if (this->m_colliderPosition.y + m_height < otherBox.m_colliderPosition.y || m_colliderPosition.y > otherBox.m_colliderPosition.y + otherBox.m_height) return false;
    return true;
}


