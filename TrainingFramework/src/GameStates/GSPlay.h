#pragma once
#include "GameStateBase.h"
#include "Player.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class Player;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents(GLfloat deltaTime) override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(float x, float y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(float x, float y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;

	int		m_CurrentFaceDirectionX;
	int		m_CurrentFaceDirectionY;
	int		m_KeyPress;
	bool	m_IsCalled;
private:
	std::shared_ptr<SpriteAnimation>	m_animationSprite;
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_score;
	std::shared_ptr<Player>		m_player;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;

};

