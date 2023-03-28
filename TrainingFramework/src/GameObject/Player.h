#pragma once
#include "CMath.h"
typedef enum STATE {IDLE, RUNNING, DASHING, BLOCKING, STUNED, SLOWED, ROOTED, DYING} State;

class Player
{
protected:
	GLint m_playerHealth;
	GLfloat m_playerSpeed;
	Vector2 m_playerPosition;
	State m_playerState;
public:
	Player();
	Player(GLint health, GLfloat speed, Vector2 position, STATE playerState);
	~Player();

	void Move(GLfloat x, GLfloat y);
	

	void SetPlayerHealth(int health);
	void SetPlayerSpeed(float speed);
	void SetPlayerPosition(Vector2 position);
	void SetPlayerState(STATE state);
	Vector2 GetPlayerPosition();
	GLint GetPlayerHealth();
	GLfloat GetPlayerSpeed();
	STATE GetPlayerState();
};

