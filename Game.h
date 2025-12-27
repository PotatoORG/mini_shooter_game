#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "EntityManager.h"


struct PlayerConfig{int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S;};
struct EnemyConfig{int SR, CR, OR, OG, OB, OT, VMIN, VMAX, SI, L; float SMIN, SMAX;};
struct BulletConfig{int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S;};
struct FontConfig{int S, R, G, B; std::string F;};
struct WindowConfig{int W, H, FL, FS;};

class Game{
	sf::RenderWindow m_window;
	EntityManager 	 m_entityManager;
	sf::Font 		 m_font;
	sf::Text 		 m_text;
	sf::Text		 m_pauseText;
	PlayerConfig	 m_playerConfig;
	EnemyConfig 	 m_enemyConfig;
	BulletConfig 	 m_bulletConfig;
	FontConfig		 m_fontConfig;
	WindowConfig	 m_windowConfig;

	int 			 m_score = 0;
	int 			 m_lastEnemySpawnedTime = 0;
	int 			 m_currentFrame = 0;
	bool 			 m_paused = false;
	bool 			 m_running = true;

	std::shared_ptr<Entity> m_player;

	void init(const std::string& configPath);
	void setPaused();
	void setUnpaused();

	void sMovement(); // System : Entity movement/position update;
	void sUserInput();
	void sLifeSpan();
	void sRender();
	void sEnemySpawner();
	void sCollision();
	void sAttack();

	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemy(std::shared_ptr<Entity> entity);
	void spawnBullet(const Vec2 & mouse_pos);
	void spawnSpecialWeapon(std::shared_ptr<Entity> entity);
	void resetGame();

public:
	Game(const std::string& configPath);

	void run();
};
#endif
