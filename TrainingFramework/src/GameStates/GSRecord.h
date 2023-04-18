#pragma once
#include "GameStateBase.h"
<<<<<<< HEAD
=======

>>>>>>> af27a35425e16caf1724adfb4a6f212fb07a45e2
class Sprite2D;
class Text;
class GameButton;


class GSRecord :
	public GameStateBase
{
public:
	GSRecord();
	~GSRecord();

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
	int m_KeyPress;
private:
	std::shared_ptr<Sprite2D>				m_background;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
<<<<<<< HEAD
	std::shared_ptr<Text>					m_lable1;
	std::shared_ptr<Text>					m_lable2;
	std::shared_ptr<Text>					m_lable3;

					

	
=======
	std::shared_ptr<Text>					m_textGameRecord;
	std::shared_ptr<Text>					m_textTop1;
	std::shared_ptr<Text>					m_textTop2;
	std::shared_ptr<Text>					m_textTop3;

	std::shared_ptr<GameButton> m_soundButtonPlay;
	std::shared_ptr<GameButton> m_soundButtonOff;
>>>>>>> af27a35425e16caf1724adfb4a6f212fb07a45e2
};

