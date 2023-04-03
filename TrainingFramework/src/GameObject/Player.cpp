#include "Player.h"


Player::Player(GLint health, GLfloat speed, Vector2 position, STATE playerState) : BoxCollider2D(INIT_POSITION, 50, 50), m_playerCurrentHealth{ health }, m_playerCurrentSpeed{ speed }, m_playerCurrentPosition{ position }, m_playerCurrentState{ playerState }
{
	//this->m_playerCurrentHealth = health;
	this->m_playerCurrentSpeed = speed;
	this->m_playerCurrentPosition = position;
	this->m_playerCurrentState = playerState;
}

Player::~Player()
{
	
}



void Player::Move(GLfloat x, GLfloat y)
{
	this->m_playerCurrentPosition.x += x;
	this->m_playerCurrentPosition.y += y;
}

void Player::Move(Vector2 v)
{
	this->m_playerCurrentPosition.x += v.x;
	this->m_playerCurrentPosition.y += v.y;
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
	//std::cout << this->GetPlayerState();
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Warrior/Down/WarriorDownIdle.tga ");


	switch (this->GetPlayerState())
	{
	case IDLE: {
			if(this->m_playerCurrentDirection == DOWN)
			{
				texture = ResourceManagers::GetInstance()->GetTexture("Warrior/Down/WarriorDownIdle.tga ");
				
			}
			if (this->m_playerCurrentDirection == LEFT)
			{
				 texture = ResourceManagers::GetInstance()->GetTexture("Warrior//Left//WarriorLeftIdle.tga");
			}
			else if (this->m_playerCurrentDirection == RIGHT)
			{
				 texture = ResourceManagers::GetInstance()->GetTexture("Warrior//Right//WarriorRightIdle.tga");
				
			}
			else if (this->m_playerCurrentDirection == UP)
			{
				 texture = ResourceManagers::GetInstance()->GetTexture("Warrior/Up/WarriorUpIdle.tga");
			}
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 5, 1, 0, 0.1f);
		m_animationSprite->Set2DPosition(this->GetPlayerPosition().x, this->GetPlayerPosition().y);
		m_animationSprite->SetSize(100, 100);
		m_listAnimation.clear();

		m_listAnimation.push_back(m_animationSprite);
		
		break;
	}
	case RUNNING: {
		if (this->m_playerCurrentDirection == DOWN)
		{
			 texture = ResourceManagers::GetInstance()->GetTexture("Warrior//Down//WarriorDownWalk.tga");
		}
		else if (this->m_playerCurrentDirection == LEFT)
		{
			
			 texture = ResourceManagers::GetInstance()->GetTexture("Warrior//Left//WarriorLeftWalk.tga");
			
		}
		else if (this->m_playerCurrentDirection == RIGHT)
		{
			 texture = ResourceManagers::GetInstance()->GetTexture("Warrior//Right//WarriorRightWalk.tga");
			
		}
		else if (this->m_playerCurrentDirection == UP)
		{
			 texture = ResourceManagers::GetInstance()->GetTexture("Warrior/Up/WarriorUpWalk.tga");
			
		}
		
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 8, 1, 0, 0.07f);
		m_animationSprite->Set2DPosition(this->GetPlayerPosition().x, this->GetPlayerPosition().y);
		m_animationSprite->SetSize(100, 100);
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

void updateWindowBoundsColision()
{
	
}



