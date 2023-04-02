#include "GSPlay.h"
#include "Player.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "SpriteAnimation.h"
#include "SkillObstacle.h"

bool isCalled;
GLfloat spawnTime;

GSPlay::GSPlay()
{

	m_KeyPress = 0;
	m_IsCalled = false;
	m_CurrentFaceDirectionX = 1;
	m_CurrentFaceDirectionY = 1;
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	m_IsCalled = false;
	const GLint PLAYER_START_HEALTH = 100;
	const GLfloat PLAYER_SPEED = 300.0f;
	const PlayerState playerState = IDLE;
	m_player = std::make_shared<Player>(100, PLAYER_SPEED, Vector2(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f), playerState);
	m_obstacle = std::make_shared<SkillObstacle>(Vector2(0, 0), 400.0f, NORMAL);
	m_obstacle = std::make_shared<SkillObstacle>(Vector2(500, 0), 400.0f, NORMAL);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_grass1.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2.0f, (float)Globals::screenHeight / 2.0f);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50.0f, 50.0f);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TextColor::RED, 1.0f);
	m_score->Set2DPosition(Vector2(5.0f, 25.0f));

	model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Warrior//Down//WarriorDownIdle.tga");
	m_playerAnimationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 5, 1, 0, 0.1f);
	m_playerAnimationSprite->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
	m_playerAnimationSprite->SetSize(100 , 100 );
	m_playerAnimationList.push_back(m_playerAnimationSprite);
	m_KeyPress = 0;

	// enemy
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("arrow-up.tga");

	m_enemy = std::make_shared<Enemy>(model, shader, texture);
	m_enemy->SetEnemyPosition((float)Globals::screenWidth, (float)Globals::screenHeight);
	m_enemy->SetEnemyDirection(atan2(m_player->GetPlayerPosition().y - m_enemy->GetEnemyPosition().y, m_player->GetPlayerPosition().x - m_enemy->GetEnemyPosition().x));
	m_enemy->SetSize(100, 100);
	enemies.push_back(m_enemy);
	activeStatus.push_back(true);
	spawnTime = 0;
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}

//Tao enemy
void GSPlay::EnemySpawn(GLfloat deltaTime) {
	std::cout << "pool" << enemies.size() << "\n";
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("arrow-up.tga");
	spawnTime += deltaTime;

	if (spawnTime > 1) {
		m_enemy = std::make_shared<Enemy>(model, shader, texture);
		m_enemy->SetRandomPosition();
		m_enemy->SetEnemyDirection(atan2(m_player->GetPlayerPosition().y - m_enemy->GetEnemyPosition().y, m_player->GetPlayerPosition().x - m_enemy->GetEnemyPosition().x));
		m_enemy->SetSize(100, 100);

		bool isActiveAll = true;
		for (int i = 0; i < enemies.size(); i++) {
			if (!activeStatus[i]) {
				isActiveAll = false;
				enemies[i] = m_enemy;
				activeStatus[i] = true;
				break;
			}
		}
		if (isActiveAll) {
			enemies.push_back(m_enemy);
			activeStatus.push_back(true);
		}

		spawnTime = 0;
	}
	for (int i = 0; i < enemies.size(); i++) {

		if (enemies[i]->GetEnemyPosition().x < 0 || enemies[i]->GetEnemyPosition().x >(float)Globals::screenWidth || enemies[i]->GetEnemyPosition().y < 0 || enemies[i]->GetEnemyPosition().y >(float)Globals::screenHeight) {
			activeStatus[i] = false;
		}
		else {
			enemies[i]->MoveTowardPlayer(m_player->GetPlayerPosition(), enemies[i]->GetEnemySpeed(), enemies[i]->GetEnemyPosition(), deltaTime, enemies[i]->GetEnemyDirection());
		}
	}
}

void GSPlay::HandleEvents(GLfloat deltatime)	
{
	m_obstacle->HandleObstacleAnimation(m_obstacleAnimationSprite, m_obstacleAnimationList);
	m_obstacleAnimationSprite->Set2DPosition(m_obstacle->GetCurrentPosition().x, m_obstacle->GetCurrentPosition().y);
	m_obstacleAnimationSprite->SetSize(100, 100);

	m_playerAnimationSprite->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
	m_playerAnimationSprite->SetSize(100, 100);
	if(m_KeyPress)
	{
		
		
		
		if (m_KeyPress & 1)//Handle event when key 'A' was pressed
		{
			m_player->SetPlayerState(RUNNING);
			m_player->SetPlayerFaceDirection(LEFT);
			m_player->Move(Vector2(-1.0f,0.0f) * m_player->GetPlayerSpeed() * deltatime);
			
		}
		if (m_KeyPress & (1 << 1))//Handle event when key 'S' was pressed
		{
			m_player->SetPlayerState(RUNNING);
			m_player->SetPlayerFaceDirection(DOWN);
			m_player->Move(Vector2(0.0f, 1.0f) * m_player->GetPlayerSpeed() * deltatime);
			

		}
		if (m_KeyPress & (1 << 2))//Handle event when key 'D' was pressed
		{
			m_player->SetPlayerState(RUNNING);
			m_player->SetPlayerFaceDirection(RIGHT);
			m_player->Move(Vector2(1.0f, 0.0f) * m_player->GetPlayerSpeed() * deltatime);
			

		}
		if (m_KeyPress & (1 << 3))//Handle event when key 'W' was pressed
		{
			m_player->SetPlayerState(RUNNING);
			m_player->SetPlayerFaceDirection(UP);
			m_player->Move(Vector2(0.0f, -1.0f) * m_player->GetPlayerSpeed() * deltatime);
			

		}
		if (m_IsCalled == false)
		{
			m_player->HandleAnimationState(m_playerAnimationSprite, m_playerAnimationList);
			m_IsCalled = true;
		}
		
	}else
	{
		
		m_player->SetPlayerState(IDLE);
		
		
	}

	//Handle key event, insert more condition if you want to handle more than 4 default key

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)//Insert more case if you want to handle more than 4 default key
{

	if (bIsPressed)
	{

		switch (key)
		{
		case KEY_MOVE_LEFT://Key 'A' was pressed
			m_KeyPress |= 1;

			break;
		case KEY_MOVE_BACKWARD://Key 'S' was pressed
			
			m_KeyPress |= 1<<1;
			
			break;
		case KEY_MOVE_RIGHT://Key 'D' was pressed
			
			m_KeyPress |= 1<<2;
			
			break;
		case KEY_MOVE_FORWARD://Key 'W' was pressed
			
			m_KeyPress |= 1<<3;
			
			break;
		default:

			break;
		}
		
		
	}
	else
	{
		switch (key)
		{
		case KEY_MOVE_LEFT://Key 'A' was released
			m_KeyPress ^= 1;
			break;
		case KEY_MOVE_BACKWARD://Key 'S' was released
			m_KeyPress ^= 1 << 1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress ^= 1 << 2;//Key 'D' was released
			break;
		case KEY_MOVE_FORWARD://Key 'W' was released
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
		if (m_IsCalled == true)
		{
			m_player->SetPlayerState(IDLE);
			m_player->HandleAnimationState(m_playerAnimationSprite, m_playerAnimationList);
			m_IsCalled = false;
		}
	}

}

//Handle button event
void GSPlay::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}

}

void GSPlay::HandleMouseMoveEvents(float x, float y)
{
	//Code to handle mouse event

}

void GSPlay::Update(float deltaTime)
{

	HandleEvents(deltaTime);
	std::cout << m_obstacle->GetCurrentPosition().x<<" " <<m_obstacle->GetCurrentPosition().y<< std::endl;
	m_obstacle->FlyToPlayer(m_obstacle->GetStartPosition(),m_player->GetPlayerPosition(), deltaTime);
	
	//Update button list
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	//Update animation list
	for (auto it : m_playerAnimationList)
	{
		it->Update(deltaTime);
	}

	for (auto it : m_obstacleAnimationList)
	{
		it->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	//Render background
	m_background->Draw();

	//Render score text
	m_score->Draw();

	//Render button list
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	//Render animation list
	for (auto it : m_playerAnimationList)
	{
		it->Draw();
	}

	for (auto it : m_obstacleAnimationList)
	{
		it->Draw();
	}

	//Render enemy
	for (int i = 0; i < enemies.size(); i++) {
		if (activeStatus[i]) {
			enemies[i]->Draw();
		}
	}
}