#pragma once
#include "CMath.h"

enum STATE { STUNE, SLOW, ROOT };
class Player
{
protected:
	GLint m_health;
	GLfloat m_speed;
	Vector2 m_position;
public:
	Player();
	Player(GLint health, GLfloat speed, Vector2 position);
	~Player();
	void SetPlayerHealth(int health);
	void SetPlayerSpeed(float speed);
	void SetPlayerPosition(Vector2 position);
	Vector2 GetPlayerPosition();
	GLint GetPlayerHealth();
	GLfloat GetPlayerSpeed();
};

