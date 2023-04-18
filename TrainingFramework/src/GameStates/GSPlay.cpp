#include "GSPlay.h"
#include "GSPlay.h"
#include "GSPlay.h"

#include <memory>
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
#include "Record.h"
#include "SpriteAnimation.h"
#include "SkillObstacle.h"

bool isCalled;

//Sound
extern std::string SoundMenu;
extern std::string SoundPlay;
extern int isPlayingSoundMenu;
extern int isPlayingSoundPlay;
extern int isPlayingSound;
extern int i;

//Score
extern GLfloat score;

GSPlay::GSPlay()
{
	m_hitAnimationDuration = 2.0f;
	m_playerHit = false;
	m_isMouseClicked = false;
	m_slowTimer = 0;
	m_stunTimer = 0;
	m_KeyPress = 0;
	m_IsCalled = false;
	m_CurrentFaceDirectionX = 1;
	m_CurrentFaceDirectionY = 1;
	m_passedCooldownTime = INIT_SKILLCOOLDOWN;
	m_spawnTimePassed = 0;
	m_isSlow = false;
	m_isStun = false;
	m_mainTimer = 0;
	m_isActiveHealItem = false;
	timeAfterItemSpawn = 0;
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
	/*m_obstacleSpawner = std::make_shared<ObstacleSpawner>(Vector2(0.f, 0.f));
	m_obstacleSpawner2 = std::make_shared<ObstacleSpawner>(Vector2(0.f, 0.2f));
	m_obstacleSpawner3 = std::make_shared<ObstacleSpawner>(Vector2(0.1f, 0.4f));
	m_obstacle = std::make_shared<SkillObstacle>();
	m_obstacle->HandleObstacleAnimation(m_obstacleAnimationSprite, m_obstacleAnimationList);
	m_obstacle2 = std::make_shared<SkillObstacle>();
	m_obstacle2->HandleObstacleAnimation(m_obstacleAnimationSprite2, m_obstacleAnimationList2);
	m_obstacle3 = std::make_shared<SkillObstacle>();
	m_obstacle3->HandleObstacleAnimation(m_obstacleAnimationSprite3, m_obstacleAnimationList3);*/

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

	// Heal Item
	texture = ResourceManagers::GetInstance()->GetTexture("chicken-leg.tga");
	m_healItem = std::make_shared<Item>(model, shader, texture);
	m_healItem->SetSize(64, 64);

	// Skill 
	texture = ResourceManagers::GetInstance()->GetTexture("Ghost.tga");
	m_skillDisplay = std::make_shared<Sprite2D>(model, shader, texture);
	m_skillDisplay->Set2DPosition((float)Globals::screenWidth - 75.0f, (float)Globals::screenHeight - 75.0f);
	m_skillDisplay->SetSize(75, 75);
	texture = ResourceManagers::GetInstance()->GetTexture("GhostCooldown.tga");
	m_skillCooldownDisplay = std::make_shared<Sprite2D>(model, shader, texture);
	m_skillCooldownDisplay->Set2DPosition((float)Globals::screenWidth - 75.0f, (float)Globals::screenHeight - 75.0f);
	m_skillCooldownDisplay->SetSize(75, 75);


	texture = ResourceManagers::GetInstance()->GetTexture("Flash.tga");
	m_skillDisplay2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_skillDisplay2->Set2DPosition((float)Globals::screenWidth - 155.0f, (float)Globals::screenHeight - 75.0f);
	m_skillDisplay2->SetSize(75, 75);
	texture = ResourceManagers::GetInstance()->GetTexture("FlashOnCooldown.tga");
	m_flashCooldownDisplay= std::make_shared<Sprite2D>(model, shader, texture);
	m_flashCooldownDisplay->Set2DPosition((float)Globals::screenWidth - 155.0f, (float)Globals::screenHeight - 75.0f);
	m_flashCooldownDisplay->SetSize(75, 75);

	// button pause
	texture = ResourceManagers::GetInstance()->GetTexture("Pause.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50.0f, 50.0f);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		//GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PAUSEGAME);
		});
	m_listButton.push_back(button);

	// end game button
	auto textureO = ResourceManagers::GetInstance()->GetTexture("Next.tga");
	m_endGameButton = std::make_shared<GameButton>(model, shader, textureO);
	m_endGameButton->Set2DPosition(660.0f, 350.0f);
	m_endGameButton->SetSize(70, 70);
	m_endGameButton->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_ENDGAME);
		});

	// You lose! text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "You lose!", TextColor::RED, 3.0f);
	m_score->Set2DPosition(Vector2(500.0f, 280.0f));

	m_player->SetPlayerFaceDirection(DOWN);
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Warrior/Down/WarriorDownIdle.tga");
	m_playerAnimationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 5, 1, 0, 0.1f);

	m_playerAnimationSprite->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
	m_playerAnimationSprite->SetSize(100, 100);
	m_playerAnimationList.clear();
	m_playerAnimationList.push_back(m_playerAnimationSprite);
	m_KeyPress = 0;

	// enemy pool
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("mine.tga");
	EnemypoolCreate(enemies1, model, shader, texture, activeStatus1, 500);
	texture = ResourceManagers::GetInstance()->GetTexture("2.tga");
	EnemypoolCreate(enemies2, model, shader, texture, activeStatus2, 700);
	texture = ResourceManagers::GetInstance()->GetTexture("3.tga");
	EnemypoolCreate(enemies3, model, shader, texture, activeStatus3, 700);
	texture = ResourceManagers::GetInstance()->GetTexture("4.tga");
	EnemypoolCreate(enemies4, model, shader, texture, activeStatus4, 900);

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
		if (isPlayingSoundMenu == 1) {
			ResourceManagers::GetInstance()->StopSound(SoundMenu);
			isPlayingSoundMenu = 0;
		}
		if (isPlayingSoundPlay == 0) {
			ResourceManagers::GetInstance()->PlaySound(SoundPlay, 1);
			isPlayingSoundPlay = 1;
		}

	}

	/*model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Effects\\Rarity Effects\\Magic effect.tga");*/
	/*m_obstacleAnimationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 9, 1, 0, 0.05f);
	m_obstacleAnimationSprite2 = std::make_shared<SpriteAnimation>(model, shader, texture, 9, 1, 0, 0.05f);
	m_obstacleAnimationSprite->Set2DPosition(500, 500);
	m_obstacleAnimationSprite2->Set2DPosition(200, 200);
	m_obstacleAnimationSprite->SetSize(100, 100);
	m_obstacleAnimationSprite2->SetSize(100, 100);
	m_obstacleAnimationList.clear();
	m_obstacleAnimationList.push_back(m_obstacleAnimationSprite);
	m_obstacleAnimationList2.push_back(m_obstacleAnimationSprite2);*/
	m_surviveTime = std::make_shared<Timer>();
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("Digital Regular.ttf");
	m_surviveTimeDisplay = std::make_shared<Text>(shader, font, m_surviveTime->DisplaySurviveTime(), TextColor::YELLOW, 3.0f);
	m_surviveTimeDisplay->Set2DPosition(Vector2(Globals::screenWidth / 2 - 110.f, 70.0f));
	m_record = std::make_shared<Record>();
	m_record->LoadRecord();
	m_record->DisplayRecord();
}

void GSPlay::Exit()
{
	m_record->AddRecord(m_surviveTime);
	m_record->SaveRecord();
}




void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}



//Tao enemy
void GSPlay::EnemySpawn(std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<bool>& activeStatus) {
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
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("mine.tga");
		m_enemy = std::make_shared<Enemy>(model, shader, texture);
		m_enemy->SetRandomPosition();
		m_enemy->SetEnemyDirection(atan2(m_player->GetPlayerPosition().y - m_enemy->GetEnemyPosition().y, m_player->GetPlayerPosition().x - m_enemy->GetEnemyPosition().x));
		m_enemy->SetSize(100, 100);
		enemies.push_back(m_enemy);
		activeStatus.push_back(true);
	}
}

void GSPlay::EnemypoolCreate(std::vector<std::shared_ptr<Enemy>>& enemies, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, std::vector<bool>& activeStatus, GLfloat speed) {
	for (int i = 0; i < 10; i++) {
		m_enemy = std::make_shared<Enemy>(model, shader, texture);
		m_enemy->SetEnemyPosition(0.0f, 0.0f);
		m_enemy->SetEnemyDirection(0.0f);
		m_enemy->SetSize(100, 100);
		m_enemy->SetEnemySpeed(speed);
		enemies.push_back(m_enemy);
		activeStatus.push_back(false);
	}
}
// Enemy controller
void GSPlay::EnemiesController(GLfloat deltaTime) {
	m_spawnTimePassed += deltaTime;
	if (m_player->GetPlayerHealth() > 0)
	{
		m_mainTimer += deltaTime;
	}

	EnemiesMovement(deltaTime, enemies1, activeStatus1);
	EnemiesMovement(deltaTime, enemies2, activeStatus2);
	EnemiesMovement(deltaTime, enemies3, activeStatus3);
	EnemiesMovement(deltaTime, enemies4, activeStatus4);

	if (m_spawnTimePassed >= m_spawnTime) {
		int ranged1 = 100;
		int ranged2 = 100;
		int ranged3 = 100;

		int random = rand() % 100;
		if (m_mainTimer < 10.0f) {
			ranged1 = 100;
			m_spawnTime = 1.5;
		}
		else if (m_mainTimer < 20.0f) {
			ranged1 = 70;
			ranged2 = 100;
			m_spawnTime = 1.25;
		}
		else if (m_mainTimer < 30.0f) {
			ranged1 = 50;
			ranged2 = 80;
			ranged3 = 100;
			m_spawnTime = 1;
		}
		else if (m_mainTimer < 40.0f) {
			ranged1 = 30;
			ranged2 = 60;
			ranged3 = 85;
			m_spawnTime = 0.75;
		}
		else {
			ranged1 = 25;
			ranged2 = 50;
			ranged3 = 75;
			m_spawnTime = 0.5;
		}

		if (random < ranged1) {
			EnemySpawn(enemies1, activeStatus1);
		}
		else if (random >= ranged1 && random < ranged2) {
			EnemySpawn(enemies2, activeStatus2);
		}
		else if (random >= ranged2 && random < ranged3) {
			EnemySpawn(enemies3, activeStatus3);
		}
		else if (random >= ranged3 && random < 100) {
			EnemySpawn(enemies4, activeStatus4);
		}
		m_spawnTimePassed = 0;
	}


}
void GSPlay::EnemiesMovement(GLfloat deltaTime, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<bool>& activeStatus) {
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
	
	m_playerAnimationSprite->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
	m_playerAnimationSprite->SetSize(100, 100);
	if (m_KeyPress)
	{



		if (m_KeyPress & 1)//Handle event when key 'A' was pressed
		{
			m_player->SetPlayerState(RUNNING);
			m_player->SetPlayerFaceDirection(LEFT);
			m_player->Move(Vector2(-1.0f, 0.0f) * m_player->GetPlayerSpeed() * deltatime);

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

	}
	else
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

			m_KeyPress |= 1 << 1;

			break;
		case KEY_MOVE_RIGHT://Key 'D' was pressed

			m_KeyPress |= 1 << 2;

			break;
		case KEY_MOVE_FORWARD://Key 'W' was pressed

			m_KeyPress |= 1 << 3;

			break;
		case KEY_SPACE://Key ' ' was pressed

			m_KeyPress |= 1 << 4;
			if (m_passedCooldownTime >= m_player->GetSkillCooldown()) {
				m_player->SetCooldownSkil(true);
				m_passedCooldownTime = 0;
			}
			break;
		case KEY_FLASH://Key 'F' was pressed
			if(!m_isStun)
			{
				m_player->FlashWithMouse(m_mouseDirection);
			}
			
			m_KeyPress |= 1 << 5;

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
		case KEY_FLASH://Key 'F' was released
			m_KeyPress ^= 1 << 5;
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
	if (bIsPressed)
	{
		m_mouseClick = Vector2(x, y);
		m_mouseDirection = m_mouseClick - m_player->GetPlayerPosition();
		m_isMouseClicked = true;
		m_IsCalled = false;
		m_mouseDirection = m_mouseDirection.Normalize();
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
		auto texture = ResourceManagers::GetInstance()->GetTexture("clickMouseEffect.tga");
		m_mouseClickAnimationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 4, 1, 0, 0.04f);
		m_mouseClickAnimationSprite->Set2DPosition(x, y);
		m_mouseClickAnimationSprite->SetSize(100, 100);

		m_mouseClickAnimationList.push_back(m_mouseClickAnimationSprite);


	}
	else
	{
		m_mouseClickAnimationList.clear();
	}


	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}

	
		//m_player->MoveByClick(Vector2(x, y), bIsPressed);
	if (m_player->GetPlayerHealth() < 1)
	{
		m_endGameButton->HandleTouchEvents(x, y, bIsPressed);
	}
	

}

void GSPlay::HandleMouseMoveEvents(float x, float y)
{
	//Code to handle mouse event

}

void GSPlay::Update(float deltaTime)
{
	if (m_player->GetPlayerHealth() > 0)
	{
		score = m_mainTimer;
	}

	//Time
	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_time = std::make_shared< Text>(shader, font, std::to_string((int)m_mainTimer), TextColor::RED, 2.0f);
	m_time->Set2DPosition(Vector2(50.0f, 680.0f));
	
	if(m_player->GetPlayerHealth()>0)
	{
		m_surviveTime->CountSurviveTime(deltaTime);
	}
	else
	{
		
	}
	m_surviveTimeDisplay->SetText(m_surviveTime->DisplaySurviveTime());
	//std::cout << "passTime" << m_passedCooldownTime << "\n";
	m_player->Skill(m_passedCooldownTime, deltaTime);
	m_player->UpdateWindowBoundsCollision();
	m_player->HandleSkillCooldown(deltaTime);
	//std::cout << m_player->GetFlashCooldownTime()<< std::endl;
	/*std::cout << m_obstacleAnimationSprite->Get2DPosition().y << " " << m_obstacleAnimationSprite2->Get2DPosition().y << std::endl;*/

	if (i == 1) {
		m_player->MoveByClick(m_playerAnimationSprite, m_playerAnimationList, m_mouseClick, m_IsCalled, m_isMouseClicked, m_mouseDirection, deltaTime);
	}
	
	//m_player->MoveByClick();
	//UpdateSpawn(deltaTime, 3);
	//UpdateSpawn(deltaTime, 4);
	//UpdateSpawn(deltaTime, 5);
	if (i == 0) {
		HandleEvents(deltaTime);
	}
	EnemiesController(deltaTime);
	/*m_obstacleSpawner->UpdateSpawn(m_obstacleAnimationSprite, m_obstacleAnimationList, m_player, 3, deltaTime, m_randomPos, &m_objectPool, m_obstacle);
	m_obstacleSpawner2->UpdateSpawn(m_obstacleAnimationSprite2, m_obstacleAnimationList2, m_player, 4, deltaTime, m_randomPos, &m_objectPool, m_obstacle2);
	m_obstacleSpawner3->UpdateSpawn(m_obstacleAnimationSprite3, m_obstacleAnimationList3, m_player, 5, deltaTime, m_randomPos, &m_objectPool, m_obstacle3);*/
	m_player->SetColliderPosition(m_player->GetPlayerPosition());

	/*m_obstacle->SetRotationFromDirection(m_obstacleAnimationSprite, m_obstacle->GetStartPosition(), m_player->GetPlayerPosition());
	m_obstacle->FlyToPlayer(m_obstacle->GetStartPosition(), m_player->GetPlayerPosition(), deltaTime);*/

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

	for (auto it : m_obstacleAnimationList2)
	{
		it->Update(deltaTime);
	}

	for (auto it : m_obstacleAnimationList3)
	{
		it->Update(deltaTime);
	}

	for (auto it : m_mouseClickAnimationList)
	{
		it->Update(deltaTime);
	}


	if (m_isSlow) {
		if (m_slowTimer < 3) {
			m_slowTimer += deltaTime;
			m_player->SetPlayerSpeed(INIT_SPEED / 2);
		}
		else {
			m_isSlow = false;
			m_slowTimer = 0;
			m_player->SetPlayerSpeed(INIT_SPEED);
		}
	}

	if (m_isStun) {
		if (m_stunTimer < 1) {
			m_stunTimer += deltaTime;
			m_player->SetPlayerSpeed(0);
			m_player->SetPlayerState(ROOTED);
			m_player->HandleAnimationState(m_playerAnimationSprite,m_playerAnimationList);
		}
		else {
			m_isStun = false;
			m_stunTimer = 0;
			m_player->SetPlayerSpeed(INIT_SPEED);
		}
	}

	for (int i = 0; i < enemies1.size(); i++) {
		if (activeStatus1[i]) {
			enemies1[i]->SetColliderPosition(enemies1[i]->GetEnemyPosition());
			if (m_player->CheckCollision(enemies1[i]->GetEnemyPosition(), 50, 50))
			{
				if (m_player->GetPlayerHealth() > 0)
				{
					ResourceManagers::GetInstance()->PlaySound("hurt.wav", 0);
				}
				
				m_hitAnimationDuration = 2.0f;
				if(m_hitAnimationDuration>0.f)
				{
					m_playerHit = true;
					m_player->SetPlayerState(HIT);
				}
			
				m_player->HandleAnimationState(m_playerAnimationSprite, m_playerAnimationList);
				activeStatus1[i] = false;
				m_player->SetPlayerHealth(m_player->GetPlayerHealth() - 1);
			}
		}
	}
	
	//Item
	timeAfterItemSpawn += deltaTime;
	if ((int)m_mainTimer % 20 == 0 && m_mainTimer>0 && timeAfterItemSpawn >1) {
			m_healItem->SetRandomPosition();
			m_isActiveHealItem = true;
			timeAfterItemSpawn = 0;
	}
	if (m_isActiveHealItem) {
		if (m_player->CheckCollision(m_healItem->GetItemPosition(), 64, 64))
		{
			m_isActiveHealItem = false;
			if (m_player->GetPlayerHealth() < 3) {
				m_player->SetPlayerHealth(m_player->GetPlayerHealth() + 1);
			}
		}
	}

	m_hitAnimationDuration -= deltaTime;
	//std::cout << m_playerHit<<std::endl;
	for (int i = 0; i < enemies2.size(); i++) {
		if (activeStatus2[i]) {
			enemies2[i]->SetColliderPosition(enemies2[i]->GetEnemyPosition());
			if (m_player->CheckCollision(enemies2[i]->GetEnemyPosition(), 50, 50))
			{

				if (m_player->GetPlayerHealth() > 0)
				{
					ResourceManagers::GetInstance()->PlaySound("hurt.wav", 0);
				}
				m_isSlow = true;
				activeStatus2[i] = false;
				m_hitAnimationDuration = 2.0f;
				if (m_hitAnimationDuration > 0.f)
				{
					m_playerHit = true;
					m_player->SetPlayerState(HIT);
				}

				m_player->HandleAnimationState(m_playerAnimationSprite, m_playerAnimationList);
				m_player->SetPlayerHealth(m_player->GetPlayerHealth() - 1);
			}
		}
	}
	for (int i = 0; i < enemies3.size(); i++) {
		if (activeStatus3[i]) {
			enemies1[i]->SetColliderPosition(enemies3[i]->GetEnemyPosition());
			if (m_player->CheckCollision(enemies3[i]->GetEnemyPosition(), 50, 50))
			{
				if (m_player->GetPlayerHealth() > 0)
				{
					ResourceManagers::GetInstance()->PlaySound("hurt.wav", 0);
				}
				m_isStun = true;
				activeStatus3[i] = false;
				m_hitAnimationDuration = 2.0f;
				if (m_hitAnimationDuration > 0.f)
				{
					m_playerHit = true;
					m_player->SetPlayerState(HIT);
				}

				m_player->HandleAnimationState(m_playerAnimationSprite, m_playerAnimationList);
				m_player->SetPlayerHealth(m_player->GetPlayerHealth() - 1);
			}
		}
	}
	for (int i = 0; i < enemies4.size(); i++) {
		if (activeStatus4[i]) {
			enemies1[i]->SetColliderPosition(enemies4[i]->GetEnemyPosition());
			if (m_player->CheckCollision(enemies4[i]->GetEnemyPosition(), 50, 50))
			{
				if (m_player->GetPlayerHealth() > 0)
				{
					ResourceManagers::GetInstance()->PlaySound("hurt.wav", 0);
				}
				activeStatus4[i] = false;
				m_hitAnimationDuration = 2.0f;
				if (m_hitAnimationDuration > 0.f)
				{
					m_playerHit = true;
					m_player->SetPlayerState(HIT);
				}

				m_player->HandleAnimationState(m_playerAnimationSprite, m_playerAnimationList);
				m_player->SetPlayerHealth(m_player->GetPlayerHealth() - 2);
			}
		}
	}
}

void GSPlay::EnemiesDraw(std::vector<std::shared_ptr<Enemy>> enemies, std::vector<bool> activeStatus) {
	for (int i = 0; i < enemies.size(); i++) {
		if (activeStatus[i]) {
			enemies[i]->Draw();
		}
	}
}

void GSPlay::Draw()
{
	//Render background
	m_background->Draw();

	m_surviveTimeDisplay->Draw();

	//Draw item
	if (m_isActiveHealItem) {
		m_healItem->Draw();
	}

	//Render button list
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	//Render animation list
	if (m_player->GetPlayerHealth() > 0)
	{
		m_time->Draw();

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
		if(m_player->GetFlashCooldownTime()<=0)
		{
			m_skillDisplay2->Draw();
		}
		else
		{
			m_flashCooldownDisplay->Draw();
		}
		
		//Render enemy
		EnemiesDraw(enemies1, activeStatus1);
		EnemiesDraw(enemies2, activeStatus2);
		EnemiesDraw(enemies3, activeStatus3);
		EnemiesDraw(enemies4, activeStatus4);
	}else
	{
		m_player->SetPlayerState(DYING);

	}
	
	
	for (auto it : m_obstacleAnimationList)
	{
		it->Draw();
	}

	for (auto it : m_mouseClickAnimationList)
	{
		it->Draw();
	}




	//Draw end game
	if (m_player->GetPlayerHealth() < 1)
	{
		
		m_score->Draw();
		m_endGameButton->Draw();
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