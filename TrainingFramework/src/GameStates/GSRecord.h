#pragma once
#include "GameStateBase.h"
#include "Record.h"

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

	std::shared_ptr<Text>					m_lable1;
	std::shared_ptr<Text>					m_lable2;
	std::shared_ptr<Text>					m_lable3;

					
	std::shared_ptr<Record> m_record;
	

	std::shared_ptr<Text>					m_textGameRecord;
	std::shared_ptr<Text>					m_textTop1;
	std::shared_ptr<Text>					m_textTop2;
	std::shared_ptr<Text>					m_textTop3;
	std::shared_ptr<Text>					m_recordTop1;
	std::shared_ptr<Text>					m_recordTop2;
	std::shared_ptr<Text>					m_recordTop3;


	std::shared_ptr<GameButton> m_soundButtonPlay;
	std::shared_ptr<GameButton> m_soundButtonOff;

};

