#include "GSPlay.h"

#include <memory>

#include "Player.h"
#include "Shader.h"
#include "ObjectPool.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "ObstacleSpawner.h"
#include "SpriteAnimation.h"
#include "SkillObstacle.h"

bool isCalled;
GLfloat spawnTime;

//Sound
extern std::string SoundMenu;
extern std::string SoundPlay;
extern int isPlayingSoundMenu;
extern int isPlayingSoundPlay;
extern int isPlayingSound;

GSPlay::GSPlay()
{

	m_KeyPress = 0;
	m_IsCalled = false;
	m_CurrentFaceDirectionX = 1;
	m_CurrentFaceDirectionY = 1;
	m_passedCooldownTime = INIT_SKILLCOOLDOWN;
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	m_IsCalled = false;
	ObjectPool<std::shared_ptr<SkillObstacle>>* objectPool = ObjectPool<std::shared_ptr<SkillObstacle>>::getInstance();
	objectPool->prepareObject(20, std::make_shared<SkillObstacle>());
	m_player = std::make_shared<Player>(MAX_HEALTH, INIT_SPEED, INIT_POSITION, INIT_STATE, INIT_ISACTIVESKILL, INIT_SKILLCOOLDOWN, INIT_SKILLTIME);
	m_obstacleSpawner = std::make_shared<ObstacleSpawner>(Vector2(0.f,0.f));
	m_obstacle = std::make_shared<SkillObstacle>(Vector2(1000, 0), 400.0f, NORMAL);
	m_obstacle->HandleObstacleAnimation(m_obstacleAnimationSprite, m_obstacleAnimationList);

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("map.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2.0f, (float)Globals::screenHeight / 2.0f);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// heart icon
	texture = ResourceManagers::GetInstance()->GetTexture("heart.tga");
	m_heartIcon = std::make_shared<Sprite2D>(model, shader, texture);
	m_heartIcon->Set2DPosition(50, 50);
	m_heartIcon->SetSize(50, 50);

	m_heartIcons.push_back(m_heartIcon);

	m_heartIcon = std::make_shared<Sprite2D>(model, shader, texture);
	m_heartIcon->Set2DPosition(100, 50);
	m_heartIcon->SetSize(50, 50);
	m_heartIcons.push_back(m_heartIcon);

	m_heartIcon = std::make_shared<Sprite2D>(model, shader, texture);
	m_heartIcon->Set2DPosition(150, 50);
	m_heartIcon->SetSize(50, 50);
	m_heartIcons.push_back(m_heartIcon);

	// Skill 
	texture = ResourceManagers::GetInstance()->GetTexture("Ghost.tga");
	m_skillDisplay = std::make_shared<Sprite2D>(model, shader, texture);
	m_skillDisplay->Set2DPosition((float)Globals::screenWidth - 75.0f, (float)Globals::screenHeight - 75.0f);
	m_skillDisplay->SetSize(75, 75);
	texture = ResourceManagers::GetInstance()->GetTexture("GhostCooldown.tga");
	m_skillCooldownDisplay = std::make_shared<Sprite2D>(model, shader, texture);
	m_skillCooldownDisplay->Set2DPosition((float)Globals::screenWidth - 75.0f, (float)Globals::screenHeight - 75.0f);
	m_skillCooldownDisplay->SetSize(75, 75);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("Back.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50.0f, 50.0f);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// button volumnPlay
	auto textureP = ResourceManagers::GetInstance()->GetTexture("MusicPlay.tga");
	m_soundButtonPlay = std::make_shared<GameButton>(model, shader, textureP);
	m_soundButtonPlay->Set2DPosition(Globals::screenWidth - 110.0f, 50.0f);
	m_soundButtonPlay->SetSize(50, 50);
	m_soundButtonPlay->SetOnClick([this]() {
		isPlayingSound = 0;
		ResourceManagers::GetInstance()->StopSound(SoundPlay);
		});

	// button volumnOff
	auto textureO = ResourceManagers::GetInstance()->GetTexture("MusicOff.tga");
	m_soundButtonOff = std::make_shared<GameButton>(model, shader, textureO);
	m_soundButtonOff->Set2DPosition(Globals::screenWidth - 110.0f, 50.0f);
	m_soundButtonOff->SetSize(50, 50);
	m_soundButtonOff->SetOnClick([this]() {
		isPlayingSound = 1;
		ResourceManagers::GetInstance()->PlaySound(SoundPlay, 1);
		});
	
	// You lose! text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "You lose!", TextColor::RED, 3.0f);
	m_score->Set2DPosition(Vector2(500.0f, 280.0f));

	//// back menu button
	//texture = ResourceManagers::GetInstance()->GetTexture("Home.tga");
	//m_backMenuButton = std::make_shared<GameButton>(model, shader, texture);
	//m_backMenuButton->Set2DPosition(500.0f, 350.0f);
	//m_backMenuButton->SetSize(50, 50);
	//m_backMenuButton->SetOnClick([this]() {
	//	GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
	//	});
	////m_listButton.push_back(button);

	model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Warrior//Down//WarriorDownIdle.tga");
	m_playerAnimationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 5, 1, 0, 0.1f);
	m_playerAnimationSprite->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
	m_playerAnimationSprite->SetSize(100 , 100 );
	m_playerAnimationList.push_back(m_playerAnimationSprite);
	m_KeyPress = 0;



	//// enemy
	//model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	//shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	//texture = ResourceManagers::GetInstance()->GetTexture("arrow-up.tga");

	//m_enemy = std::make_shared<Enemy>(model, shader, texture);
	//m_enemy->SetEnemyPosition((float)Globals::screenWidth, (float)Globals::screenHeight);
	//m_enemy->SetEnemyDirection(atan2(m_player->GetPlayerPosition().y - m_enemy->GetEnemyPosition().y, m_player->GetPlayerPosition().x - m_enemy->GetEnemyPosition().x));
	//m_enemy->SetSize(100, 100);
	//enemies.push_back(m_enemy);
	//activeStatus.push_back(true);
	

	if (isPlayingSound == 1)
	{
		ResourceManagers::GetInstance()->StopSound(SoundMenu);
		isPlayingSoundMenu = 0;

		ResourceManagers::GetInstance()->PlaySound(SoundPlay);
		isPlayingSoundPlay = 1;
	}
	
	

}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
	if (isPlayingSound == 1)
	{
		ResourceManagers::GetInstance()->StopSound(SoundPlay);
		isPlayingSoundPlay = 0;
	}
}

void GSPlay::Resume()
{
}

//void GSPlay::CheckCollision()
//{
//	CheckCollision();
//}

//Tao enemy
void GSPlay::EnemySpawn(GLfloat deltaTime) {
	
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("mine.tga");
	spawnTime += deltaTime;

	if (spawnTime > 1) {
		

		bool isActiveAll = true;
		for (int i = 0; i < enemies.size(); i++) {
			if (!activeStatus[i]) {
				isActiveAll = false;
				enemies[i]->SetRandomPosition();
				enemies[i]->SetEnemyDirection(atan2(m_player->GetPlayerPosition().y - enemies[i]->GetEnemyPosition().y, m_player->GetPlayerPosition().x - enemies[i]->GetEnemyPosition().x));
				activeStatus[i] = true;
				break;
			}
		}
		if (isActiveAll) {
			m_enemy = std::make_shared<Enemy>(model, shader, texture);
			m_enemy->SetRandomPosition();
			m_enemy->SetEnemyDirection(atan2(m_player->GetPlayerPosition().y - m_enemy->GetEnemyPosition().y, m_player->GetPlayerPosition().x - m_enemy->GetEnemyPosition().x));
			m_enemy->SetSize(100, 100);
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
	m_obstacleAnimationSprite->Set2DPosition(m_obstacle->GetCurrentPosition().x, m_obstacle->GetCurrentPosition().y);
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
		if (m_KeyPress & (1 << 4))//Handle event when key space was pressed
		{
			if (m_passedCooldownTime >= m_player->GetSkillCooldown()) {
				m_player->SetCooldownSkil(true);
				m_passedCooldownTime = 0;
			}
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
		case KEY_SPACE://Key ' ' was pressed

			m_KeyPress |= 1 << 4;

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
		case KEY_SPACE://Key ' ' was released
			m_KeyPress ^= 1 << 4;
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

	if (isPlayingSound == 1)
	{
		m_soundButtonPlay->HandleTouchEvents(x, y, bIsPressed);
	}
	else
	{
		m_soundButtonOff->HandleTouchEvents(x, y, bIsPressed);
	}

}

void GSPlay::HandleMouseMoveEvents(float x, float y)
{
	//Code to handle mouse event
	 
}

void GSPlay::Update(float deltaTime)
{
	//std::cout << "passTime" << m_passedCooldownTime << "\n";
	m_player->Skill(m_passedCooldownTime, deltaTime);

	m_obstacleSpawner->UpdateSpawn(deltaTime);
	//std::cout << m_obstacleSpawner->GetSpawnPosition().x <<" "<< m_obstacleSpawner->GetSpawnPosition().y<<std::endl;
	HandleEvents(deltaTime);
	EnemySpawn(deltaTime);
	m_player->SetColliderPosition(m_player->GetPlayerPosition());
	
	m_obstacle->SetRotationFromDirection(m_obstacleAnimationSprite, m_obstacle->GetStartPosition(), m_player->GetPlayerPosition());
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

	//Update sound button
	m_soundButtonPlay->Update(deltaTime);
	m_soundButtonOff->Update(deltaTime);
	
	for (int i = 0; i < enemies.size(); i++) {
		if (activeStatus[i]) {
			enemies[i]->SetColliderPosition(enemies[i]->GetEnemyPosition());
			if (m_player->CheckCollision(enemies[i]->GetEnemyPosition(), 50, 50))
			{
				//std::cout << "lol";
				activeStatus[i] = false;
				m_player->SetPlayerHealth(m_player->GetPlayerHealth() - 1);
			}
				

		}
	}
}

void GSPlay::Draw()
{
	//Render background
	m_background->Draw();


	//Render button list
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	//Render animation list
	if (m_player->GetPlayerHealth() > 0)
	{
		
		for (auto it : m_playerAnimationList)
		{
			it->Draw();
		}

		if (!m_player->IsCooldownSkill()) {
			m_skillDisplay->Draw();
		}
		else {
			m_skillCooldownDisplay->Draw();
		}
		//Render enemy
		for (int i = 0; i < enemies.size(); i++) {
			if (activeStatus[i]) {
				enemies[i]->Draw();
			}
		}
	}
	

	for (auto it : m_obstacleAnimationList)
	{
		it->Draw();
	}

	

	//Draw end game
	if (m_player->GetPlayerHealth() < 1)
	{
		m_score->Draw();
		//m_backMenuButton->Draw();
	}

	// Draw sound button
	if (isPlayingSound == 1)
	{
		m_soundButtonPlay->Draw();
	}
	else
	{
		m_soundButtonOff->Draw();
	}

	//Draw heart
	if (m_player->GetPlayerHealth() > 0)
	{
		m_heartIcons[0]->Draw();
	}
	if (m_player->GetPlayerHealth() > 1)
	{
		m_heartIcons[1]->Draw();
	}
	if (m_player->GetPlayerHealth() > 2)
	{
		m_heartIcons[2]->Draw();
	}
}