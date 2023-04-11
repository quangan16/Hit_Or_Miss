#include "GSPickMove.h"
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

int i = 0;

//Sound
extern std::string SoundMenu;
extern std::string SoundPlay;
extern int isPlayingSoundMenu;
extern int isPlayingSoundPlay;
extern int isPlayingSound;


GSPickMove::GSPickMove()
{
	m_KeyPress = 0;
}


GSPickMove::~GSPickMove()
{
}



void GSPickMove::Init()
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

	// button playbykeyboard
	texture = ResourceManagers::GetInstance()->GetTexture("play.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 870.0f, 300.0f);
	button->SetSize(150, 150);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		i = 0;
		});
	m_listButton.push_back(button);

	// button playbymouse
	texture = ResourceManagers::GetInstance()->GetTexture("play.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 370.0f, 300.0f);
	button->SetSize(150, 150);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		i = 1;
		});
	m_listButton.push_back(button);

	// Setting title		
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("WoodBeadsDemoRegular.otf");
	m_textGameSetting = std::make_shared< Text>(shader, font, "Move by keyboard", TextColor::WHITE, 1.5f);
	m_textGameSetting->Set2DPosition(Vector2(250.0f, 150.0f));

	// Volumn title
	m_textGameVolumn = std::make_shared< Text>(shader, font, "Move by mouse", TextColor::WHITE, 1.5f);
	m_textGameVolumn->Set2DPosition(Vector2(780.0f, 150.0f));

	m_KeyPress = 0;

}

void GSPickMove::Exit()
{
}


void GSPickMove::Pause()
{
}

void GSPickMove::Resume()
{
	if (isPlayingSound == 1)
	{
		if (isPlayingSoundMenu == 0)
		{
			ResourceManagers::GetInstance()->PlaySound(SoundMenu, 1);
			isPlayingSoundMenu = 1;
		}
		if (isPlayingSoundPlay == 1)
		{
			ResourceManagers::GetInstance()->StopSound(SoundPlay);
		}
	}
}


void GSPickMove::HandleEvents(GLfloat deltaTime)
{
}



void GSPickMove::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSPickMove::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPickMove::HandleMouseMoveEvents(float x, float y)
{
}

void GSPickMove::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

}

void GSPickMove::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_textGameSetting->Draw();
	m_textGameVolumn->Draw();
}
