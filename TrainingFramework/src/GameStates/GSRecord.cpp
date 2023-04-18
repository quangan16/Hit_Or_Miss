#include "GSRecord.h"
<<<<<<< HEAD
#include "GSSetting.h"
=======
>>>>>>> af27a35425e16caf1724adfb4a6f212fb07a45e2
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
<<<<<<< HEAD
	
=======
	m_KeyPress = 0;
>>>>>>> af27a35425e16caf1724adfb4a6f212fb07a45e2
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

<<<<<<< HEAD
	

	// Volumn title
	/*m_textGameVolumn = std::make_shared< Text>(shader, font, "Music", TextColor::WHITE, 2.0f);
	m_textGameVolumn->Set2DPosition(Vector2(500.0f, 280.0f));

	m_KeyPress = 0;*/
=======
	// Setting title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Palamecia Titling.otf");
	m_textGameRecord = std::make_shared< Text>(shader, font, "Record", TextColor::WHITE, 2.0f);
	m_textGameRecord->Set2DPosition(Vector2(600.0f, 80.0f));

	// Top 1 title
	font = ResourceManagers::GetInstance()->GetFont("Palamecia Titling.otf");
	m_textTop1 = std::make_shared< Text>(shader, font, "TOP 1: ", TextColor::WHITE, 2.0f);
	m_textTop1->Set2DPosition(Vector2(500.0f, 280.0f));

	// Top 2 title
	m_textTop2 = std::make_shared< Text>(shader, font, "TOP 2: ", TextColor::WHITE, 2.0f);
	m_textTop2->Set2DPosition(Vector2(500.0f, 340.0f));

	// Top 3 title
	m_textTop3 = std::make_shared< Text>(shader, font, "TOP 3: ", TextColor::WHITE, 2.0f);
	m_textTop3->Set2DPosition(Vector2(500.0f, 400.0f));

	m_KeyPress = 0;
>>>>>>> af27a35425e16caf1724adfb4a6f212fb07a45e2

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

<<<<<<< HEAD
	/*if (isPlayingSound == 1)
	{
		m_soundButtonPlay->HandleTouchEvents(x, y, bIsPressed);
	}
	else
	{
		m_soundButtonOff->HandleTouchEvents(x, y, bIsPressed);
	}*/

=======
>>>>>>> af27a35425e16caf1724adfb4a6f212fb07a45e2
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


<<<<<<< HEAD
	/*m_soundButtonPlay->Update(deltaTime);
	m_soundButtonOff->Update(deltaTime);*/
=======
>>>>>>> af27a35425e16caf1724adfb4a6f212fb07a45e2
}

void GSRecord::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}

<<<<<<< HEAD
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
=======
	m_textGameRecord->Draw();
	m_textTop1->Draw();
	m_textTop2->Draw();
	m_textTop3->Draw();
>>>>>>> af27a35425e16caf1724adfb4a6f212fb07a45e2
}
