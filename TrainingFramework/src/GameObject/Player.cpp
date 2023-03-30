#include "Player.h"


Player::Player(){}

Player::Player(GLint health, GLfloat speed, Vector2 position, STATE state)
{
	//this->m_playerCurrentHealth = health;
	this->m_playerCurrentSpeed = speed;
	this->m_playerCurrentPosition = position;
	this->m_playerCurrentState = state;
};

Player::~Player(){};

void Player::Move(GLfloat x, GLfloat y)
{
	this->m_playerCurrentPosition.x += x;
	this->m_playerCurrentPosition.y += y;
}

void Player::SetPlayerHealth(int health) {
	m_playerCurrentHealth = health;
};

void Player::SetPlayerSpeed(float speed) {
	m_playerCurrentSpeed = speed;
}
;
void Player::SetPlayerPosition(Vector2 position) {
	m_playerCurrentPosition = position;
};

void Player::SetPlayerState(PlayerState state ) {
	m_playerCurrentState = state;
};

void Player::SetPlayerFaceDirection(PlayerDirection faceDirection)
{
	m_playerCurrentDirection = faceDirection;
};


GLint Player::GetPlayerHealth() {
	return m_playerCurrentHealth;
};

GLfloat Player::GetPlayerSpeed() {
	return m_playerCurrentSpeed;
};

Vector2 Player::GetPlayerPosition() {
	return m_playerCurrentPosition;
};

PlayerState Player::GetPlayerState() {
	return this->m_playerCurrentState;
};

PlayerDirection Player::GetPlayerFaceDirection()
{
	return m_playerCurrentDirection;
}


void Player::HandleAnimationState(std::shared_ptr<SpriteAnimation>	&m_animationSprite, std::list<std::shared_ptr<SpriteAnimation>>	&m_listAnimation)
{
	std::cout << this->GetPlayerState();
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Warrior/Down/WarriorDownIdle.tga ");;


	switch (this->GetPlayerState())
	{
	case IDLE: {
			if(this->GetPlayerFaceDirection() == DOWN)
			{
				texture = ResourceManagers::GetInstance()->GetTexture("Warrior/Down/WarriorDownIdle.tga ");;
				
			}
			else if (this->GetPlayerFaceDirection() == LEFT)
			{
				 texture = ResourceManagers::GetInstance()->GetTexture("Warrior//Left//WarriorLeftIdle.tga");
			}
			else if (this->GetPlayerFaceDirection() == RIGHT)
			{
				 texture = ResourceManagers::GetInstance()->GetTexture("Warrior//Right//WarriorRightIdle.tga");
				
			}
			else if (this->GetPlayerFaceDirection() == UP)
			{
				 texture = ResourceManagers::GetInstance()->GetTexture("Warrior/Up/WarriorUpIdle.tga");
			}
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 5, 1, 0, 0.1f);
		

		m_listAnimation.clear();
		m_listAnimation.push_back(m_animationSprite);
		
		break;
	}
	case RUNNING: {
		if (this->GetPlayerFaceDirection() == DOWN)
		{
			 texture = ResourceManagers::GetInstance()->GetTexture("Warrior//Down//WarriorDownWalk.tga");
		}
		else if (this->GetPlayerFaceDirection() == LEFT)
		{
			
			 texture = ResourceManagers::GetInstance()->GetTexture("Warrior//Left//WarriorLeftWalk.tga");
			
		}
		else if (this->GetPlayerFaceDirection() == RIGHT)
		{
			 texture = ResourceManagers::GetInstance()->GetTexture("Warrior//Right//WarriorRightWalk.tga");
			
		}
		else if (this->GetPlayerFaceDirection() == UP)
		{
			 texture = ResourceManagers::GetInstance()->GetTexture("Warrior/Up/WarriorUpWalk.tga");
			
		}
		
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 8, 1, 0, 0.07f);
		
		m_listAnimation.clear();
		m_listAnimation.push_back(m_animationSprite);

		break;
	}
	case DASHING: {
		if (this->GetPlayerFaceDirection() == DOWN)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == LEFT)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == RIGHT)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == UP)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		//m_animationSprite->Set2DPosition(this->GetPlayerPosition().x, this->GetPlayerPosition().y);
		
		m_listAnimation.push_back(m_animationSprite);

		break;
	}

	case BLOCKING: {
		if (this->GetPlayerFaceDirection() == DOWN)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == LEFT)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == RIGHT)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == UP)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		//m_animationSprite->Set2DPosition(this->GetPlayerPosition().x, this->GetPlayerPosition().y);
		//m_animationSprite->SetSize(120, -100);
		m_listAnimation.clear();
		m_listAnimation.push_back(m_animationSprite);
		break;
	}
	case HIT: {
		if (this->GetPlayerFaceDirection() == DOWN)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == LEFT)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == RIGHT)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == UP)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		//m_animationSprite->Set2DPosition(this->GetPlayerPosition().x, this->GetPlayerPosition().y);
		//m_animationSprite->SetSize(120, -100);
		m_listAnimation.clear();
		m_listAnimation.push_back(m_animationSprite);
		break;

	}
	case BURNED:
	{
		if (this->GetPlayerFaceDirection() == DOWN)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == LEFT)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == RIGHT)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == UP)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		//m_animationSprite->Set2DPosition(this->GetPlayerPosition().x, this->GetPlayerPosition().y);
		//m_animationSprite->SetSize(120, -100);
		m_listAnimation.clear();
		m_listAnimation.push_back(m_animationSprite);
		break;
	}
	case SLOWED: {
		if (this->GetPlayerFaceDirection() == DOWN)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == LEFT)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == RIGHT)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == UP)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		m_animationSprite->Set2DPosition(this->GetPlayerPosition().x, this->GetPlayerPosition().y);
		//m_animationSprite->SetSize(120, -100);
		m_listAnimation.push_back(m_animationSprite);
		break;
	}
	case ROOTED: {
		if (this->GetPlayerFaceDirection() == DOWN)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == LEFT)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == RIGHT)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == UP)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		m_animationSprite->Set2DPosition(this->GetPlayerPosition().x, this->GetPlayerPosition().y);
		m_animationSprite->SetSize(120, -100);
		m_listAnimation.push_back(m_animationSprite);
		break;
	}
	case DYING: {
		if (this->GetPlayerFaceDirection() == DOWN)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == LEFT)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == RIGHT)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		else if (this->GetPlayerFaceDirection() == UP)
		{
			m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		}
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		m_animationSprite->Set2DPosition(this->GetPlayerPosition().x, this->GetPlayerPosition().y);
		m_animationSprite->SetSize(120, -100);
		m_listAnimation.push_back(m_animationSprite);
		break;
	}
	default:
		break;
	}

}



