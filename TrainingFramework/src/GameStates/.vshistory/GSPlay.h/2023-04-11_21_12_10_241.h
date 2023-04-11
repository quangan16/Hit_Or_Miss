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

	void	EnemySpawn(std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<bool>& activeStatus);
	void	EnemiesMovement(GLfloat deltaTime, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<bool>& activeStatus);
	void	EnemiesController(GLfloat deltaTime);
	void	EnemypoolCreate(std::vector<std::shared_ptr<Enemy>>& enemies, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, std::vector<bool>& activeStatus, GLfloat speed);
	void	EnemiesDraw(std::vector<std::shared_ptr<Enemy>> enemies, std::vector<bool> activeStatus);
	void	HandleEvents(GLfloat deltaTime) override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(float x, float y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(float x, float y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;

	int		m_CurrentFaceDirectionX;
	int		m_CurrentFaceDirectionY;
	Vector2 m_mouseClick;
	Vector2 m_mouseDirection;
	bool m_isMouseClicked;
	int		m_KeyPress;
	bool	m_IsCalled;
private:
	Vector2 m_randomPos;
	GLfloat m_counter;
	std::shared_ptr<SpriteAnimation>	m_playerAnimationSprite;
	std::shared_ptr<SpriteAnimation>	m_obstacleAnimationSprite;
	std::shared_ptr<SpriteAnimation>	m_obstacleAnimationSprite2;
	std::shared_ptr<SpriteAnimation>	m_obstacleAnimationSprite3;
	std::shared_ptr<SpriteAnimation>	m_mouseClickAnimationSprite;
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_score;
	std::shared_ptr<Player>		m_player;
	std::shared_ptr<SkillObstacle> m_obstacle;
	std::shared_ptr<SkillObstacle> m_obstacle2;
	std::shared_ptr<SkillObstacle> m_obstacle3;
	std::shared_ptr<ObstacleSpawner>	m_obstacleSpawner;
	std::shared_ptr<ObstacleSpawner>	m_obstacleSpawner2;
	std::shared_ptr<ObstacleSpawner>	m_obstacleSpawner3;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_playerAnimationList;
	std::list<std::shared_ptr<SpriteAnimation>>	m_obstacleAnimationList;
	std::list<std::shared_ptr<SpriteAnimation>>	m_obstacleAnimationList2;
	std::list<std::shared_ptr<SpriteAnimation>>	m_obstacleAnimationList3;
	std::list<std::shared_ptr<SpriteAnimation>>	m_mouseClickAnimationList;

	std::shared_ptr<Enemy> m_enemy;
	std::vector<std::shared_ptr<Enemy>> enemies1;
	std::vector<std::shared_ptr<Enemy>> enemies2;
	std::vector<std::shared_ptr<Enemy>> enemies3;
	std::vector<std::shared_ptr<Enemy>> enemies4;
	std::vector<bool> activeStatus1;
	std::vector<bool> activeStatus2;
	std::vector<bool> activeStatus3;
	std::vector<bool> activeStatus4;
	ObjectPool<std::shared_ptr<SkillObstacle>>* m_objectPool;
	std::shared_ptr<Sprite2D>	m_skillCooldownDisplay;
	GLfloat m_passedCooldownTime;
	std::shared_ptr<Sprite2D> m_skillDisplay;

	std::shared_ptr<GameButton> m_soundButtonPlay;
	std::shared_ptr<GameButton> m_soundButtonOff;

	//std::shared_ptr<GameButton> m_backMenuButton;

	std::shared_ptr<Sprite2D>	m_heartIcon;
	std::vector<std::shared_ptr<Sprite2D>> m_heartIcons;

	GLfloat m_mainTimer;
	GLfloat m_spawnTime;
	GLfloat m_spawnTimePassed;
	GLfloat m_slowTimer;
	GLfloat m_stunTimer;

	bool m_isSlow;
	bool m_isStun;

};