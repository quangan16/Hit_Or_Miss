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


bool isCalled = false;


GSPlay::GSPlay()
{
	
	m_KeyPress = 0;
	m_isCalled = false;
	m_playerFaceDirectionX = 1;
}


GSPlay::~GSPlay()
{
}	


void GSPlay::Init()
{
	
	m_player = std::make_shared<Player>(100, 2.0f, Vector2(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f), State::IDLE);
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
	
	HandleAnimationState();
	m_KeyPress = 0;
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




void GSPlay::HandleAnimationState()
{
	std::cout << m_player->GetPlayerState();
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Warrior_1.tga");
	
	
	switch (m_player->GetPlayerState())
	{
	case IDLE: {
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		m_animationSprite->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
		m_animationSprite->SetSize(120*m_playerFaceDirectionX, -100);

		m_listAnimation.clear();
		m_listAnimation.push_back(m_animationSprite);

		break;
	}
	case RUNNING: {
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 1, 0.1f);
		//m_animationSprite->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
		//m_animationSprite->SetSize(120, -100);
		m_listAnimation.clear();
		m_listAnimation.push_back(m_animationSprite);

		break;
	}
	case DASHING: {
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		//m_animationSprite->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
		//m_animationSprite->SetSize(120, -100);
		m_listAnimation.push_back(m_animationSprite);

		break;
	}

	case BLOCKING: {
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		//m_animationSprite->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
		//m_animationSprite->SetSize(120, -100);
		m_listAnimation.clear();
		m_listAnimation.push_back(m_animationSprite);
		break;
	}
	case SLOWED: {
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		m_animationSprite->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
		//m_animationSprite->SetSize(120, -100);
		m_listAnimation.push_back(m_animationSprite);
		break;
	}
	case ROOTED: {
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		m_animationSprite->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
		m_animationSprite->SetSize(120, -100);
		m_listAnimation.push_back(m_animationSprite);
		break;
	}
	case DYING: {
		m_animationSprite = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		m_animationSprite->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
		m_animationSprite->SetSize(120, -100);
		m_listAnimation.push_back(m_animationSprite);
		break;
	}
	}
	return;
}

void GSPlay::HandleEvents()
{

	m_animationSprite->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
	
	if(m_KeyPress)
	{
		m_player->SetPlayerState(RUNNING);
		if (m_isCalled == false)
		{
			m_animationSprite->SetSize(120, -100);
			
			HandleAnimationState();
			m_isCalled = true;
		}
		
		if (m_KeyPress & 1)//Handle event when key 'A' was pressed
		{
			m_playerFaceDirectionX = -1;
			m_animationSprite->SetSize(120*m_playerFaceDirectionX, -100);
			m_player->Move(-1.0f * m_player->GetPlayerSpeed(), 0.0f);

		}
		if (m_KeyPress & (1 << 1))//Handle event when key 'S' was pressed
		{
			m_animationSprite->SetSize(120* m_playerFaceDirectionX, -100);
			m_player->Move(0.0f, 1.0f * m_player->GetPlayerSpeed());

		}
		if (m_KeyPress & (1 << 2))//Handle event when key 'D' was pressed
		{
			m_playerFaceDirectionX = 1;
			m_animationSprite->SetSize(120 * m_playerFaceDirectionX, -100);
			m_player->Move(1.0f*m_player->GetPlayerSpeed(), 0.0f);

		}
		if (m_KeyPress & (1 << 3))//Handle event when key 'W' was pressed
		{
			m_animationSprite->SetSize(120 * m_playerFaceDirectionX, -100);
			m_player->Move(0.0f, -1.0f*m_player->GetPlayerSpeed());

		}
		
		
		
	}
	else
	{
		m_player->SetPlayerState(IDLE);
		if (m_isCalled == true)
		{

			HandleAnimationState();
			m_isCalled = false;
		}
		m_animationSprite->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
		
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
	}
	
}

//Handle button event
void GSPlay::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
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
	HandleEvents();

	std::cout << m_isCalled<<std::endl;
	//Update button list
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	//Update animation list
	for (auto it : m_listAnimation)
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
	for (auto it : m_listAnimation)
	{
		it->Draw();
	}
}