#include "GSPauseGame.h"
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

GSPauseGame::GSPauseGame()
{
	m_KeyPress = 0;
}


GSPauseGame::~GSPauseGame()
{
}



void GSPauseGame::Init()
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

	// button volumnPlay
	auto textureP = ResourceManagers::GetInstance()->GetTexture("MusicPlay.tga");
	m_soundButtonPlay = std::make_shared<GameButton>(model, shader, textureP);
	m_soundButtonPlay->Set2DPosition(Globals::screenWidth - 520.0f, 265.0f);
	m_soundButtonPlay->SetSize(50, 50);
	m_soundButtonPlay->SetOnClick([this]() {
		isPlayingSound = 0;
		isPlayingSoundPlay = 0;
		ResourceManagers::GetInstance()->StopSound(SoundPlay);
		});

	// button volumnOff
	auto textureO = ResourceManagers::GetInstance()->GetTexture("MusicOff.tga");
	m_soundButtonOff = std::make_shared<GameButton>(model, shader, textureO);
	m_soundButtonOff->Set2DPosition(Globals::screenWidth - 520.0f, 265.0f);
	m_soundButtonOff->SetSize(50, 50);
	m_soundButtonOff->SetOnClick([this]() {
		isPlayingSound = 1;
		isPlayingSoundPlay = 1;
		ResourceManagers::GetInstance()->PlaySound(SoundPlay, 1);
		});

	// button home
	texture = ResourceManagers::GetInstance()->GetTexture("Home.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 720.0f, 400.0f);
	button->SetSize(100, 100);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(button);

	// button replay
	texture = ResourceManagers::GetInstance()->GetTexture("Replay.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 530.0f, 400.0f);
	button->SetSize(100, 100);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);

	// Setting title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("WoodBeadsDemoRegular.otf");
	m_textGameSetting = std::make_shared< Text>(shader, font, "PauseGame", TextColor::WHITE, 3.0f);
	m_textGameSetting->Set2DPosition(Vector2(480.0f, 80.0f));

	// Volumn title
	m_textGameVolumn = std::make_shared< Text>(shader, font, "Music", TextColor::WHITE, 2.0f);
	m_textGameVolumn->Set2DPosition(Vector2(500.0f, 280.0f));

	m_KeyPress = 0;
	if (isPlayingSound == 1) {
		//ResourceManagers::GetInstance()->StopSound(SoundPlay);
		//ResourceManagers::GetInstance()->PlaySound(SoundMenu, 1);
	}
}

void GSPauseGame::Exit()
{
}


void GSPauseGame::Pause()
{
	//ResourceManagers::GetInstance()->StopSound(SoundMenu);
}

void GSPauseGame::Resume()
{

}


void GSPauseGame::HandleEvents(GLfloat deltaTime)
{
}



void GSPauseGame::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSPauseGame::HandleTouchEvents(float x, float y, bool bIsPressed)
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

void GSPauseGame::HandleMouseMoveEvents(float x, float y)
{
}

void GSPauseGame::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}


	m_soundButtonPlay->Update(deltaTime);
	m_soundButtonOff->Update(deltaTime);
}

void GSPauseGame::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	if (isPlayingSound == 1)
	{
		m_soundButtonPlay->Draw();
	}
	else
	{
		m_soundButtonOff->Draw();
	}
	m_textGameSetting->Draw();
	m_textGameVolumn->Draw();
}
