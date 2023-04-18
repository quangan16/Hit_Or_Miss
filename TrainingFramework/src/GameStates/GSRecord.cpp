#include "GSRecord.h"
#include "GSSetting.h"
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
#include "Math.h"


//Sound
extern std::string SoundMenu;
extern std::string SoundPlay;
extern int isPlayingSoundMenu;
extern int isPlayingSoundPlay;
extern int isPlayingSound;

GSRecord::GSRecord()
{
	
}


GSRecord::~GSRecord()
{
}



void GSRecord::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("3995243.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button back
	texture = ResourceManagers::GetInstance()->GetTexture("Back.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50.0f, 50.0f);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	

	// Volumn title
	/*m_textGameVolumn = std::make_shared< Text>(shader, font, "Music", TextColor::WHITE, 2.0f);
	m_textGameVolumn->Set2DPosition(Vector2(500.0f, 280.0f));

	m_KeyPress = 0;*/

}

void GSRecord::Exit()
{
}


void GSRecord::Pause()
{
}

void GSRecord::Resume()
{
}


void GSRecord::HandleEvents(GLfloat deltaTime)
{
}



void GSRecord::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSRecord::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}

	/*if (isPlayingSound == 1)
	{
		m_soundButtonPlay->HandleTouchEvents(x, y, bIsPressed);
	}
	else
	{
		m_soundButtonOff->HandleTouchEvents(x, y, bIsPressed);
	}*/

}

void GSRecord::HandleMouseMoveEvents(float x, float y)
{
}

void GSRecord::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}


	/*m_soundButtonPlay->Update(deltaTime);
	m_soundButtonOff->Update(deltaTime);*/
}

void GSRecord::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	/*if (isPlayingSound == 1)
	{
		m_soundButtonPlay->Draw();
	}
	else
	{
		m_soundButtonOff->Draw();
	}
	m_textGameSetting->Draw();
	m_textGameVolumn->Draw();*/
}
