#include "Player.h"


Player::Player() {};

Player::Player(GLint health, GLfloat speed, Vector2 position) {
	m_health = health;
	m_speed = speed;
	m_position = position;
};

Player::~Player(){};

void Player::SetPlayerHealth(int health) {
	m_health = health;
};
void Player::SetPlayerSpeed(float speed) {
	m_speed = speed;
}
;
void Player::SetPlayerPosition(Vector2 position) {
	m_position = position;
};
Vector2 Player::GetPlayerPosition() {
	return m_position;
};
GLint Player::GetPlayerHealth() {
	return m_health;
};
GLfloat Player::GetPlayerSpeed() {
	return m_speed;
};



