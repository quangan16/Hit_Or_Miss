#include "BoxCollider2D.h"


BoxCollider2D::BoxCollider2D(Vector2 objectPos, float width, float height) {
    this->objectPosition = objectPos;
    m_width = width;
    m_height = height;
}


bool BoxCollider2D::CheckCollisionWithOtherBox(const BoxCollider2D& otherBox) const {
    if (objectPosition.x + m_width < otherBox.objectPosition.x || objectPosition.x > otherBox.objectPosition.x + otherBox.m_width) return false;
    if (objectPosition.y + m_height < otherBox.objectPosition.y || objectPosition.y > otherBox.objectPosition.y + otherBox.m_height) return false;
    return true;
}


