//#include "GSSetting.h"
//#include "Shader.h"
//#include "Texture.h"
//#include "Model.h"
//#include "Camera.h"
//#include "Font.h"
//#include "Sprite2D.h"
//#include "Sprite3D.h"
//#include "Text.h"
//#include "GameButton.h"
//#include "SpriteAnimation.h"
//#include "Math.h"
//
//
////Sound
//extern std::string SoundMenu;
//extern std::string SoundPlay;
//extern int isPlayingSoundMenu;
//extern int isPlayingSoundPlay;
//extern int isPlayingSound;
//
//GSSetting::GSSetting()
//{
//	m_KeyPress = 0;
//}
//
//
//GSSetting::~GSSetting()
//{
//}
//
//
//
//void GSSetting::Init()
//{
//	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
//	auto texture = ResourceManagers::GetInstance()->GetTexture("3995243.tga");
//
//	// background
//	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
//	m_background = std::make_shared<Sprite2D>(model, shader, texture);
//	m_background->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f);
//	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);
//
//	// button back
//	texture = ResourceManagers::GetInstance()->GetTexture("Back.tga");
//	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
//	button->Set2DPosition(Globals::screenWidth - 50.0f, 50.0f);
//	button->SetSize(50, 50);
//	button->SetOnClick([this]() {
//		GameStateMachine::GetInstance()->PopState();
//		});
//	m_listButton.push_back(button);
//
//	// button volumnPlay
//	auto textureP = ResourceManagers::GetInstance()->GetTexture("MusicPlay.tga");
//	m_soundButtonPlay = std::make_shared<GameButton>(model, shader, textureP);
//	m_soundButtonPlay->Set2DPosition(Globals::screenWidth - 500.0f, 260.0f);
//	m_soundButtonPlay->SetSize(50, 50);
//	m_soundButtonPlay->SetOnClick([this]() {
//		isPlayingSound = 0;
//		ResourceManagers::GetInstance()->StopSound(SoundMenu);
//		});
//
//	// button volumnOff
//	auto textureO = ResourceManagers::GetInstance()->GetTexture("MusicOff.tga");
//	m_soundButtonOff = std::make_shared<GameButton>(model, shader, textureO);
//	m_soundButtonOff->Set2DPosition(Globals::screenWidth - 500.0f, 260.0f);
//	m_soundButtonOff->SetSize(50, 50);
//	m_soundButtonOff->SetOnClick([this]() {
//		isPlayingSound = 1;
//		ResourceManagers::GetInstance()->PlaySound(SoundMenu, 1);
//		});
//
//	// Setting title
//	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
//	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("WoodBeadsDemoRegular.otf");
//	m_textGameSetting = std::make_shared< Text>(shader, font, "Setting", TextColor::WHITE, 3.0f);
//	m_textGameSetting->Set2DPosition(Vector2(540.0f, 80.0f));
//
//	// Volumn title
//	m_textGameVolumn = std::make_shared< Text>(shader, font, "Volumn", TextColor::WHITE, 2.0f);
//	m_textGameVolumn->Set2DPosition(Vector2(500.0f, 280.0f));
//
//	m_KeyPress = 0;
//
//}
//
//void GSSetting::Exit()
//{
//}
//
//
//void GSSetting::Pause()
//{
//}
//
//void GSSetting::Resume()
//{
//}
//
//
//void GSSetting::HandleEvents(GLfloat deltaTime)
//{
//}
//
//void GSSetting::HandleKeyEvents(int key, bool bIsPressed)
//{
//}
//
//void GSSetting::HandleTouchEvents(float x, float y, bool bIsPressed)
//{
//	for (auto button : m_listButton)
//	{
//		if (button->HandleTouchEvents(x, y, bIsPressed))
//		{
//			break;
//		}
//	}
//
//	if (isPlayingSound == 1)
//	{
//		m_soundButtonPlay->HandleTouchEvents(x, y, bIsPressed);
//	}
//	else
//	{
//		m_soundButtonOff->HandleTouchEvents(x, y, bIsPressed);
//	}
//
//}
//
//void GSSetting::HandleMouseMoveEvents(float x, float y)
//{
//}
//
//void GSSetting::Update(float deltaTime)
//{
//	m_background->Update(deltaTime);
//	for (auto it : m_listButton)
//	{
//		it->Update(deltaTime);
//	}
//
//
//	m_soundButtonPlay->Update(deltaTime);
//	m_soundButtonOff->Update(deltaTime);
//}
//
//void GSSetting::Draw()
//{
//	m_background->Draw();
//	for (auto it : m_listButton)
//	{
//		it->Draw();
//	}
//
//	if (isPlayingSound == 1)
//	{
//		m_soundButtonPlay->Draw();
//	}
//	else
//	{
//		m_soundButtonOff->Draw();
//	}
//	m_textGameSetting->Draw();
//	m_textGameVolumn->Draw();
//}
