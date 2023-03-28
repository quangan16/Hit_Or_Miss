#include "Player.h"


Player::Player() {};

Player::Player(GLint health, GLfloat speed, Vector2 position, STATE state) {
	m_playerHealth = health;
	m_playerSpeed = speed;
	m_playerPosition = position;
	m_playerState = state;
};

Player::~Player(){};

void Player::Move(GLfloat x, GLfloat y)
{
	this->m_playerPosition.x += x;
	this->m_playerPosition.y += y;
}

void Player::SetPlayerHealth(int health) {
	m_playerHealth = health;
};

void Player::SetPlayerSpeed(float speed) {
	m_playerSpeed = speed;
}
;
void Player::SetPlayerPosition(Vector2 position) {
	m_playerPosition = position;
};

void Player::SetPlayerState(State state ) {
	m_playerState = state;
};

GLint Player::GetPlayerHealth() {
	return m_playerHealth;
};

GLfloat Player::GetPlayerSpeed() {
	return m_playerSpeed;
};

Vector2 Player::GetPlayerPosition() {
	return m_playerPosition;
};

State Player::GetPlayerState() {
	return m_playerState;
};





