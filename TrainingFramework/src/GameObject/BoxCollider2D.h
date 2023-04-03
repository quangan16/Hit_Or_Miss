#pragma once
#include <cmath>
#include <GameConfig.h>

class BoxCollider2D {
public:
    // Constructor
    BoxCollider2D(Vector2 objectPos, float width, float height);
    
    // Check collision with another box collider
    bool CheckCollisionWithOtherBox(const BoxCollider2D& otherBox) const;
      
    

private:
    Vector2 objectPosition;
    float m_width, m_height;
};

