#include "Player.h"


Player::Player(GLint health, GLfloat speed, Vector2 position, STATE playerState, GLboolean isCooldownSkill, GLfloat skillCooldown, GLfloat skillActiveTime)
	: BoxCollider2D(INIT_POSITION, 10, 22), m_playerCurrentHealth{ health }, m_playerCurrentSpeed{ speed }, m_playerCurrentPosition{ position }, m_playerCurrentState{ playerState },
	m_isCooldownSkill{ isCooldownSkill }, m_skillCooldown{ skillCooldown }, m_skillActiveTime{ skillActiveTime }
{
	//this->m_playerCurrentHealth = health;
	this->m_playerCurrentSpeed = speed;
	this->m_playerCurrentPosition = position;
	this->m_playerCurrentState = playerState;
	this->m_isCooldownSkill = isCooldownSkill;
	this->m_skillCooldown = skillCooldown;
	this->m_skillActiveTime = skillActiveTime;
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

void Player::SetPlayerState(PlayerState state) {
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

Vector2 Player::GetPlayerPosition() const{
	return m_playerCurrentPosition;
};

PlayerState Player::GetPlayerState() const{
	return this->m_playerCurrentState;
};

PlayerDirection Player::GetPlayerFaceDirection()
{
	return m_playerCurrentDirection;
}

Vector2 Player::GetPlayerMouseClickDestination()
{
	return m_mouseDestination;
}

void Player::SetPlayerMouseClickDestination(Vector2 destination)
{
	m_mouseDestination = destination;
	//std::cout << m_mouseDestination.x <<" "<< m_mouseDestination.x;
}



void Player::MoveByClick(std::shared_ptr<SpriteAnimation>& m_animationSprite, std::list<std::shared_ptr<SpriteAnimation>>& m_listAnimation, Vector2 mouseClick, bool &isCalled, bool &isMouseClicked, Vector2 mouseDirection, GLfloat deltaTime)
{
	m_animationSprite->Set2DPosition(this->GetPlayerPosition().x, this->GetPlayerPosition().y);
	m_animationSprite->SetSize(120, 120);
	GLfloat directionX = mouseClick.x - this->GetPlayerPosition().x;
	GLfloat directionY = mouseClick.y - this->GetPlayerPosition().y;
	GLfloat distance = sqrt(directionX * directionX + directionY * directionY);
	GLfloat angleDirection = (atan2(directionY, directionX) - M_PI / 2);
	//std::cout <<distance<< std::endl;
	// check if player has reached destination
	if (distance <= 3.0f) { // choose your own threshold here

		if (isCalled == true)
		{
			this->SetPlayerState(IDLE);
			this->HandleAnimationState(m_animationSprite, m_listAnimation);
			isCalled = false;
		}
		return; // stop moving player
	}
	else if (isMouseClicked)
	{
		if (angleDirection <= M_PI / 4 && angleDirection >= -M_PI / 4)
		{
			this->SetPlayerState(RUNNING);
			this->SetPlayerFaceDirection(DOWN);
		}
		if (angleDirection >= -5 * M_PI / 4 && angleDirection <= -3 * M_PI / 4)
		{
			this->SetPlayerState(RUNNING);
			this->SetPlayerFaceDirection(UP);
		}
		if (angleDirection <= -M_PI / 4 && angleDirection >= -3 * M_PI / 4)
		{
			this->SetPlayerState(RUNNING);
			this->SetPlayerFaceDirection(RIGHT);
		}
		if (angleDirection >= M_PI / 4 && angleDirection <= M_PI / 2 || angleDirection <= -5 * M_PI / 4 && angleDirection >= -3 * M_PI / 2)
		{
			this->SetPlayerState(RUNNING);
			this->SetPlayerFaceDirection(LEFT);
		}
		if (isCalled == false)
		{
			std::cout << ((atan2(directionY, directionX) - M_PI / 2)) << std::endl;

			this->HandleAnimationState(m_animationSprite, m_listAnimation);
			isCalled = true;
		}

		this->Move(mouseDirection * this->GetPlayerSpeed() * deltaTime);


	}

	
}

void Player::FlashWithMouse(Vector2 clickPos, bool bIsPressed, GLfloat cooldown, GLfloat m_counter)
{
	if (bIsPressed) {
		Vector2 direction = clickPos - this->GetPlayerPosition();
		direction = direction.Normalize();
		if (this->GetPlayerPosition().x != clickPos.x && this->GetPlayerPosition().y != clickPos.y)
		{
			this->Move(direction * this->GetPlayerSpeed());

		}

	}
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
		if (this->m_playerCurrentDirection == DOWN)
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
		m_animationSprite->SetSize(120, 120);
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
		m_animationSprite->SetSize(120, 120);
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
		m_animationSprite->Set2DPosition(this->GetPlayerPosition().x, this->GetPlayerPosition().y);
		
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

void Player::UpdateWindowBoundsCollision()
{
	if (this->GetColliderPosition().x - this->m_width / 2 <= 0.f) {
		this->SetPlayerPosition(Vector2(this->GetPlayerPosition().x + m_width / 2, this->GetPlayerPosition().y));
	}
	else if (this->GetColliderPosition().x + this->m_width / 2 >= Globals::screenWidth) {
		this->SetPlayerPosition(Vector2(this->GetPlayerPosition().x - m_width / 2, this->GetPlayerPosition().y));
	}
	if (this->GetColliderPosition().y + this->m_height / 2 >= Globals::screenHeight) {
		this->SetPlayerPosition(Vector2(this->GetPlayerPosition().x, this->GetPlayerPosition().y - m_height / 2));
	}
	else if (this->GetColliderPosition().y - this->m_height / 2 <= 0.f) {
		this->SetPlayerPosition(Vector2(	this->GetPlayerPosition().x, this->GetPlayerPosition().y + m_height / 2));
	}
}

Vector2  Player::GetPlayerRandomPosCircle(GLfloat radius)
{

	bool isGetPos = false;
	Vector2 finalPos;
	GLfloat rand1;
	GLfloat rand2;
	// Seed the random number generator with the current time

	if (isGetPos == false)
	{
		// Generate two random numbers between 0 and 1
		rand1 = static_cast<GLfloat>(std::rand()) / RAND_MAX;
		rand2 = static_cast<GLfloat>(std::rand()) / RAND_MAX;
		isGetPos = true;
	}


	// Calculate the angle and radius of the point within the circle
	GLfloat angle = rand1 * 2 * M_PI;
	GLfloat radius_point = sqrt(rand2) * radius;

	// Convert the angle from radians to degrees if necessary
	GLfloat angle_degrees = angle * 180 / M_PI;

	// Convert polar coordinates to Cartesian coordinates
	GLfloat x = radius_point * cos(angle);
	GLfloat y = radius_point * sin(angle);

	// Add center coordinates to get final position
	finalPos.x = this->m_playerCurrentPosition.x + x;
	finalPos.y = this->m_playerCurrentPosition.y + y;




	return finalPos;
}
void Player::Skill(GLfloat& passedTime, GLfloat deltaTime) {
	if (passedTime >= m_skillCooldown) {
		m_isCooldownSkill = false;
	}
	if (m_isCooldownSkill) {
		if (passedTime < m_skillActiveTime) {
			SetPlayerSpeed(INIT_SPEED * 1.2f);
		}
		else
		{
			SetPlayerSpeed(INIT_SPEED);
		}
	}
	passedTime += deltaTime;
}
GLfloat Player::GetSkillCooldown() {
	return m_skillCooldown;
};
void Player::SetCooldownSkil(GLboolean isCooldown) {
	m_isCooldownSkill = isCooldown;
};
GLfloat Player::IsCooldownSkill() {
	return m_isCooldownSkill;
};

GLfloat Player::GetFlashCooldownTime()
{
	return m_flashCooldown;
}