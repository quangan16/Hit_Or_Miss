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




GSPlay::GSPlay()
{
	m_KeyPress = 0;
}


GSPlay::~GSPlay()
{
}	


void GSPlay::Init()
{

	m_player = std::make_shared<Player>(100, 10.0f, Vector2(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f), State::NORMAL);
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

	//animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Warrior_1.tga");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
	obj->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
	obj->SetSize(120, -100);
	m_listAnimation.push_back(obj);
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
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Warrior_1.tga");
	switch (m_player->GetPlayerState())
	{
	case NORMAL:
	
		
		std::shared_ptr<SpriteAnimation> obj1 = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		obj1->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
		obj1->SetSize(120, -100);
		m_listAnimation.push_back(obj1);
		
		break;

	case RUNNING:
		std::shared_ptr<SpriteAnimation> obj2 = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		obj2->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
		obj2->SetSize(120, -100);
		m_listAnimation.push_back(obj2);

		break;

	case DASHING:
		std::shared_ptr<SpriteAnimation> obj3 = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		obj3->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
		obj3->SetSize(120, -100);
		m_listAnimation.push_back(obj2);

		break;
		break;

	case SLOWED:
		std::shared_ptr<SpriteAnimation> obj4 = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		obj4->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
		obj4->SetSize(120, -100);
		m_listAnimation.push_back(obj2);
		break;

	case BLOCKING:
		std::shared_ptr<SpriteAnimation> obj5 = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		obj5->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
		obj5->SetSize(120, -100);
		m_listAnimation.push_back(obj2);
		break;

	case ROOTED:
		std::shared_ptr<SpriteAnimation> obj6 = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		obj6->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
		obj6->SetSize(120, -100);
		m_listAnimation.push_back(obj2);
		break;

	case DYING:
		std::shared_ptr<SpriteAnimation> obj7 = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 17, 0, 0.1f);
		obj7->Set2DPosition(m_player->GetPlayerPosition().x, m_player->GetPlayerPosition().y);
		obj7->SetSize(120, -100);
		m_listAnimation.push_back(obj2);
		break;

		default;
		break;
	}
}

void GSPlay::HandleEvents()
{
	//Handle key event, insert more condition if you want to handle more than 4 default key
	if (m_KeyPress & 1)//Handle event when key 'A' was pressed
	{
		m_player->SetPlayerState(RUNNING);
		m_player->Move(-10.0f, 0.0f);
		std::cout << m_player->GetPlayerPosition().x;


	}
	if (m_KeyPress & (1 << 1))//Handle event when key 'S' was pressed
	{
		//Code to handle event
	}
	if (m_KeyPress & (1 << 2))//Handle event when key 'D' was pressed
	{
		//Code to handle event
	}
	if (m_KeyPress & (1 << 3))//Handle event when key 'W' was pressed
	{
		//Code to handle event
	}
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