#pragma once
#include <cmath>
#include <GameConfig.h>
#include "Collider2D.h"

class BoxCollider2D : public Collider2D {
public:
    // Constructor
    BoxCollider2D();
    BoxCollider2D(Vector2 objectPos, GLfloat width, GLfloat height);


    // Check collision with another box collider
    bool CheckCollision(Vector2 pos, float width, float height) override;


protected:
    GLfloat m_width;
    GLfloat m_height;
};

