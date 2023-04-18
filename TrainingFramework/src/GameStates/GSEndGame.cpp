#include "GSEndGame.h"
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

GLfloat score = 0;
GLfloat high_score = 0;


GSEndGame::GSEndGame()
{
	m_KeyPress = 0;
}


GSEndGame::~GSEndGame()
{
}



void GSEndGame::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("3995243.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	//// button back
	//texture = ResourceManagers::GetInstance()->GetTexture("Back.tga");
	//std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	//button->Set2DPosition(Globals::screenWidth - 50.0f, 50.0f);
	//button->SetSize(50, 50);
	//button->SetOnClick([this]() {
	//	GameStateMachine::GetInstance()->PopState();
	//	});
	//m_listButton.push_back(button);

	// button home
	texture = ResourceManagers::GetInstance()->GetTexture("Home.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 870.0f, 300.0f);
	button->SetSize(150, 150);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(button);

	// button replay
	texture = ResourceManagers::GetInstance()->GetTexture("Replay.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 370.0f, 300.0f);
	button->SetSize(150, 150);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);
	if (score > high_score) {
		high_score = score;
	}
	// Score title		
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_textScore = std::make_shared< Text>(shader, font, "Score: " + std::to_string((int)score), TextColor::WHITE, 2.0f);
	m_textScore->Set2DPosition(Vector2(300.0f, 150.0f));

	// HightScore title
	m_textHighScore = std::make_shared< Text>(shader, font, "High Score: " + std::to_string((int)high_score), TextColor::WHITE, 2.0f);
	m_textHighScore->Set2DPosition(Vector2(750.0f, 150.0f));

	m_KeyPress = 0;
	if (isPlayingSoundPlay == 1) {
		ResourceManagers::GetInstance()->StopSound(SoundPlay);
		isPlayingSoundPlay = 0;
	}
}

void GSEndGame::Exit()
{
}


void GSEndGame::Pause()
{
}

void GSEndGame::Resume()
{
}


void GSEndGame::HandleEvents(GLfloat deltaTime)
{
}



void GSEndGame::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSEndGame::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSEndGame::HandleMouseMoveEvents(float x, float y)
{
}

void GSEndGame::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

}

void GSEndGame::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_textScore->Draw();
	m_textHighScore->Draw();
}
