#pragma once
#include "Sprite2D.h"
#include "BoxCollider2D.h"
class Item : public Sprite2D, public BoxCollider2D
{
protected:
	std::string m_enemyType;
	GLfloat m_enemySpeed;
	GLfloat m_enemyDirection;
public:
	Item(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);

	void SetItemPosition(GLfloat x, GLfloat y) { Set2DPosition(x, y); }
	Vector2 GetItemPosition() { return Get2DPosition(); }

	void SetRandomPosition();
};