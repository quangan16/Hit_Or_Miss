#pragma once
#include "Enemy.h"
#include "GameStateBase.h"
#include "ObjectPool.h"
#include "Player.h"
#include "SkillObstacle.h"

class ObstacleSpawner;
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
	void	UpdateSpawn(GLfloat deltaTime, GLfloat intervalTime);
	void	EnemySpawn(GLfloat deltaTime);
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
	Vector2 m_randomPos;
	GLfloat m_counter;
	std::shared_ptr<SpriteAnimation>	m_playerAnimationSprite;
	std::shared_ptr<SpriteAnimation>	m_obstacleAnimationSprite;
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_score;
	std::shared_ptr<Player>		m_player;
	std::shared_ptr<SkillObstacle> m_obstacle;
	std::shared_ptr<ObstacleSpawner>	m_obstacleSpawner;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_playerAnimationList;
	std::list<std::shared_ptr<SpriteAnimation>>	m_obstacleAnimationList;
	ObjectPool<std::shared_ptr<SkillObstacle>>* m_objectPool;
	std::shared_ptr<Enemy> m_enemy;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<bool> activeStatus;
	
	std::shared_ptr<Sprite2D>	m_skillCooldownDisplay;
	GLfloat m_passedCooldownTime;
	std::shared_ptr<Sprite2D> m_skillDisplay;

	std::shared_ptr<GameButton> m_soundButtonPlay;
	std::shared_ptr<GameButton> m_soundButtonOff;
};