#pragma once
#include "CMath.h"
typedef enum STATE {IDLE, RUNNING, DASHING, BLOCKING, HIT, BURNED, SLOWED, ROOTED, DYING} PlayerState;

class Player
{
protected:
	GLint m_playerHealth;
	GLfloat m_playerSpeed;
	Vector2 m_playerPosition;
	PlayerState m_playerState;
public:
	Player();
	Player(GLint health, GLfloat speed, Vector2 position, STATE playerState);
	~Player();

	void Move(GLfloat x, GLfloat y);
	void MoveToMouseClickedPos(GLfloat desX, GLfloat desY, bool bIsPressed);
		
	

	void SetPlayerHealth(int health);
	void SetPlayerSpeed(float speed);
	void SetPlayerPosition(Vector2 position);
	void SetPlayerState(STATE state);
	Vector2 GetPlayerPosition();
	GLint GetPlayerHealth();
	GLfloat GetPlayerSpeed();
	STATE GetPlayerState();
};

