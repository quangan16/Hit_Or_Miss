#pragma once
#include "CMath.h"
#include "BoxCollider2D.h"
#include "SpriteAnimation.h"
#include "ResourceManagers.h"
#include "GameConfig.h"

using PlayerState = enum STATE { IDLE, RUNNING, DASHING, BLOCKING, HIT, BURNED, SLOWED, ROOTED, DYING };
using PlayerDirection = enum DIRECTION { DOWN, LEFT, RIGHT, UP };

class Player : public BoxCollider2D
{
	
protected:
	
	
	GLint		m_playerCurrentHealth;
	GLfloat		m_playerCurrentSpeed;
	Vector2		m_playerCurrentPosition;
	PlayerDirection		m_playerCurrentDirection;
	PlayerState m_playerCurrentState;
	std::shared_ptr<SpriteAnimation>	m_animationSprite;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	GLboolean	m_isCooldownSkill;
	GLfloat		m_skillActiveTime;
	GLfloat		m_skillCooldown;
	Vector2 m_mouseDestination;
public:
	
	Player();
	Player(GLint health, GLfloat speed, Vector2 position, STATE playerState, GLboolean isActiveSkill, GLfloat m_skillCooldown, GLfloat m_skillActiveTime);
	~Player();

	void Move(GLfloat x, GLfloat y);
	void Move(Vector2 v);
	//void MoveToMouseClickedPos(GLfloat desX, GLfloat desY, bool bIsPressed);
	//void HandlePlayerFaceDirection();
	void HandleAnimationState(std::shared_ptr<SpriteAnimation>& m_animationSprite, std::list<std::shared_ptr<SpriteAnimation>>& m_listAnimation);

	void SetPlayerHealth(GLint health);
	void SetPlayerSpeed(GLfloat speed);
	void SetPlayerPosition(Vector2 position);
	void SetPlayerState(STATE state);
	void SetPlayerFaceDirection(PlayerDirection faceDirection);
	void SetPlayerMouseClickDestination(Vector2 destination);

	Vector2 GetPlayerPosition() const;
	GLint GetPlayerHealth();
	GLfloat GetPlayerSpeed();
	GLfloat SetPlayerSpeed();
	STATE GetPlayerState() const;
	PlayerDirection GetPlayerFaceDirection();
	Vector2 GetPlayerMouseClickDestination();
	void UpdateWindowBoundsCollision();
	void MoveByClick(std::shared_ptr<SpriteAnimation>& m_animationSprite, std::list<std::shared_ptr<SpriteAnimation>>& m_listAnimation, Vector2 mouseClick, bool& isCalled, bool &isMouseClicked, Vector2 mouseDirection, GLfloat deltaTime);
	Vector2 GetPlayerRandomPosCircle(GLfloat radius);
	GLfloat GetSkillCooldown();
	GLfloat IsCooldownSkill();
	void SetCooldownSkil(GLboolean isCooldown);
	void Skill(GLfloat& passedTime, GLfloat deltaTime);
	void FlashWithMouse(Vector2 clickPos, bool bIsPressed);
};

