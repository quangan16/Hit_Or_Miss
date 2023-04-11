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
	m_isMouseClicked = false;
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
	m_counter = 0;
	std::srand(std::time(nullptr));
	m_IsCalled = false;
	m_objectPool = ObjectPool<std::shared_ptr<SkillObstacle>>::getInstance();
	m_objectPool->prepareObject(20, std::make_shared<SkillObstacle>());
	m_player = std::make_shared<Player>(MAX_HEALTH, INIT_SPEED, INIT_POSITION, INIT_STATE, INIT_ISACTIVESKILL, INIT_SKILLCOOLDOWN, INIT_SKILLTIME);
	m_obstacleSpawner = std::make_shared<ObstacleSpawner>(Vector2(0.f,0.f));
	m_obstacleSpawner2 = std::make_shared<ObstacleSpawner>(Vector2(0.f, 0.2f));
	m_obstacleSpawner3 = std::make_shared<ObstacleSpawner>(Vector2(0.1f, 0.4f));
	m_obstacle = std::make_shared<SkillObstacle>();
	m_obstacle->HandleObstacleAnimation(m_obstacleAnimationSprite, m_obstacleAnimationList);
	m_obstacle2 = std::make_shared<SkillObstacle>();
	m_obstacle2->HandleObstacleAnimation(m_obstacleAnimationSprite2, m_obstacleAnimationList2);
	m_obstacle3 = std::make_shared<SkillObstacle>();
	m_obstacle3->HandleObstacleAnimation(m_obstacleAnimationSprite3, m_obstacleAnimationList3);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("desertoasis.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2.0f, (float)Globals::screenHeight / 2.0f);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

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
	
	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TextColor::RED, 1.0f);
	m_score->Set2DPosition(Vector2(5.0f, 25.0f));

	model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Warrior/Down/WarriorDownIdle.tga");
	m_playerAnimationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 5, 1, 0, 0.1f);
	m_playerAnimationSprite->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
	m_playerAnimationSprite->SetSize(100 , 100 );
	m_playerAnimationList.push_back(m_playerAnimationSprite);
	m_KeyPress = 0;

	model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Effects\\Rarity Effects\\Magic effect.tga");
	m_obstacleAnimationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 9, 1, 0, 0.05f);
	m_obstacleAnimationSprite2 = std::make_shared<SpriteAnimation>(model, shader, texture, 9, 1, 0, 0.05f);
	m_obstacleAnimationSprite->Set2DPosition(500,500);
	m_obstacleAnimationSprite2->Set2DPosition(200,200);
	m_obstacleAnimationSprite->SetSize(100, 100);
	m_obstacleAnimationSprite2->SetSize(100, 100);
	m_obstacleAnimationList.clear();
	m_obstacleAnimationList.push_back(m_obstacleAnimationSprite);
	m_obstacleAnimationList2.push_back(m_obstacleAnimationSprite2);


	// enemy
	/*model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("arrow-up.tga");*/

	/*m_enemy = std::make_shared<Enemy>(model, shader, texture);
	m_enemy->SetEnemyPosition((float)Globals::screenWidth, (float)Globals::screenHeight);
	m_enemy->SetEnemyDirection(atan2(m_player->GetPlayerPosition().y - m_enemy->GetEnemyPosition().y, m_player->GetPlayerPosition().x - m_enemy->GetEnemyPosition().x));
	m_enemy->SetSize(100, 100);
	enemies.push_back(m_enemy);
	activeStatus.push_back(true);
	spawnTime = 0;*/

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

//Tao enemy
//void GSPlay::EnemySpawn(GLfloat deltaTime) {
//	
//	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
//	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
//	auto texture = ResourceManagers::GetInstance()->GetTexture("arrow-up.tga");
//	spawnTime += deltaTime;
//
//	if (spawnTime > 1) {
//		
//
//		bool isActiveAll = true;
//		for (int i = 0; i < enemies.size(); i++) {
//			if (!activeStatus[i]) {
//				isActiveAll = false;
//				enemies[i]->SetRandomPosition();
//				enemies[i]->SetEnemyDirection(atan2(m_player->GetPlayerPosition().y - enemies[i]->GetEnemyPosition().y, m_player->GetPlayerPosition().x - enemies[i]->GetEnemyPosition().x));
//				activeStatus[i] = true;
//				break;
//			}
//		}
//		if (isActiveAll) {
//			m_enemy = std::make_shared<Enemy>(model, shader, texture);
//			m_enemy->SetRandomPosition();
//			m_enemy->SetEnemyDirection(atan2(m_player->GetPlayerPosition().y - m_enemy->GetEnemyPosition().y, m_player->GetPlayerPosition().x - m_enemy->GetEnemyPosition().x));
//			m_enemy->SetSize(100, 100);
//			enemies.push_back(m_enemy);
//			activeStatus.push_back(true);
//		}
//
//		spawnTime = 0;
//	}
//	for (int i = 0; i < enemies.size(); i++) {
//
//		if (enemies[i]->GetEnemyPosition().x < 0 || enemies[i]->GetEnemyPosition().x >(float)Globals::screenWidth || enemies[i]->GetEnemyPosition().y < 0 || enemies[i]->GetEnemyPosition().y >(float)Globals::screenHeight) {
//			activeStatus[i] = false;
//		}
//		else {
//			enemies[i]->MoveTowardPlayer(m_player->GetPlayerPosition(), enemies[i]->GetEnemySpeed(), enemies[i]->GetEnemyPosition(), deltaTime, enemies[i]->GetEnemyDirection());
//		}
//	}
//}



void GSPlay::HandleEvents(GLfloat deltatime)	
{
	
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
	if(bIsPressed)
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
		
		
	}else
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

void GSPlay:: UpdateSpawn(GLfloat deltaTime, GLfloat intervalTime) {
	
	m_counter += deltaTime;
	

	// Generate random position off-screen
	GLfloat x = 0.f, y= 0.f;
	int side = std::rand() % 4; // choose a random side of the offscreen area
	switch (side)
	{
	case 0: // top side
		x = std::rand() % (Globals::screenWidth - 50) + 50;
		y = -std::rand() % Globals::screenWidth;
		break;
	case 1: // right side
		x = Globals::screenWidth + std::rand() % 50;
		y = std::rand() % (Globals::screenHeight - 50) + 50;
		break;
	case 2: // bottom side
		x = std::rand() % (Globals::screenWidth - 50) + 50;
		y = Globals::screenHeight + std::rand() % 50;
		break;
	case 3: // left side
		x = -std::rand() % 50;
		y = std::rand() % (Globals::screenHeight - 50) + 50;
		break;
	}

	// Print the random position


	if (m_counter > intervalTime)
	{
		m_randomPos = m_player->GetPlayerRandomPosCircle(100.0f);

		m_obstacleSpawner->SetSpawnPosition(Vector2(x, y));
		m_obstacle = m_objectPool->acquireObject();
		m_obstacle->SetStartPosition(m_obstacleSpawner->GetSpawnPosition());
		m_obstacle->SetCurrentPosition(m_obstacle->GetStartPosition());
		
		m_obstacle->HandleObstacleAnimation(m_obstacleAnimationSprite, m_obstacleAnimationList);
		//std::cout << "new!";
		m_counter = 0.f;
		// Spawn enemy at generated position with chosen direction
		m_objectPool->getAvailableObjectsSize();
		/* add enemy to game world */
	}
	if (m_obstacle->GetCurrentPosition().x < -60.f || m_obstacle->GetCurrentPosition().x >(float)Globals::screenWidth + 60.f || m_obstacle->GetCurrentPosition().y < -60.f || m_obstacle->GetCurrentPosition().y >(float)Globals::screenHeight+ 60.f) {

		m_objectPool->releaseObject(m_obstacle);
		//std::cout << m_obstacle->GetCurrentPosition().x<<std::endl;
		
	}
	else {
		m_obstacle->SetObstacleRotation(m_obstacleAnimationSprite, m_obstacle->GetStartPosition(), m_randomPos);
		m_obstacle->FlyToTarget(m_obstacle->GetStartPosition(), m_randomPos, deltaTime);
		//std::cout << m_obstacle->GetCurrentPosition().x<<std::endl;
		
	}

}

void GSPlay::Update(float deltaTime)
{
	std::cout<<m_obstacleAnimationSprite->Get2DPosition().y<<" "<< m_obstacleAnimationSprite2->Get2DPosition().y<<std::endl;
	
		
	m_player->MoveByClick(m_playerAnimationSprite, m_playerAnimationList, m_mouseClick, m_IsCalled, m_isMouseClicked, m_mouseDirection, deltaTime);
	//m_player->MoveByClick();
	//UpdateSpawn(deltaTime, 3);
	//UpdateSpawn(deltaTime, 4);
	//UpdateSpawn(deltaTime, 5);
	//m_obstacle->FlyToTarget(m_obstacleSpawner->GetSpawnPosition(),m_player->GetPlayerRandomPosCircle(100.0f), deltaTime);

	m_obstacleSpawner->UpdateSpawn(m_obstacleAnimationSprite, m_obstacleAnimationList, m_player, 3, deltaTime, m_randomPos, &m_objectPool, m_obstacle);
	m_obstacleSpawner2->UpdateSpawn(m_obstacleAnimationSprite2, m_obstacleAnimationList2, m_player, 4, deltaTime, m_randomPos, &m_objectPool, m_obstacle2);
	m_obstacleSpawner3->UpdateSpawn(m_obstacleAnimationSprite3, m_obstacleAnimationList3,  m_player, 5 , deltaTime, m_randomPos, &m_objectPool, m_obstacle3);
	//std::cout<<m_obstacleSpawner->m_counter<<" "<< m_obstacleSpawner2->m_counter<<" "<< m_obstacleSpawner3->m_counter<<std::endl;
	//HandleEvents(deltaTime);
	//HandleEvents2(deltaTime, GSPlay::m_isMouseClicked);
	//EnemySpawn(deltaTime);
	m_player->SetColliderPosition(m_player->GetPlayerPosition());
	m_player->UpdateWindowBoundsCollision();
	
	//m_player->CheckCollision(m_obstacle->SetColliderPosition());

		

	
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

	//Update sound button
	m_soundButtonPlay->Update(deltaTime);
	m_soundButtonOff->Update(deltaTime);
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

	for (auto it : m_obstacleAnimationList2)
	{
		it->Draw();
	}

	for (auto it : m_obstacleAnimationList3)
	{
		it->Draw();
	}

	for (auto it : m_mouseClickAnimationList)
	{
		it->Draw();
	}

	//Render enemy
	for (int i = 0; i < enemies.size(); i++) {
		if (activeStatus[i]) {
			enemies[i]->Draw();
		}
	}

	if (!m_player->IsCooldownSkill()) {
		m_skillDisplay->Draw();
	}
	else {
		m_skillCooldownDisplay->Draw();
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
}