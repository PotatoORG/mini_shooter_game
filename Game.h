#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

struct PlayerConfig{int SR, CR, FR, FG, FB, OR, OG, OT, V, float S};
struct EnemyConfig{int SR, CR, OR, OG, OB, OT, VMIN, VMAX, SI, float SMIN, SMAX};
struct BulletConfig{int SR, CR, FR, FG, FB, OR, OG, OT, V, L, float S};

class Game{
	sf::RenderWindow m_window;
	EntityManager 	 m_entities;
	sf::Font 		 m_font;
	sf::text 		 m_text;
	PlayerConfig	 m_playerConfig;
	EnemyConfig 	 m_enemyConfig;
	BulletConfig 	 m_bulletConfig;
	int 			 m_score = 0;
	int 			 m_lastEnemySpawnedTime = 0;
	int 			 m_currentFrame;
	bool 			 m_paused = false;
	bool 			 m_running = true;

	std::shared_ptr<Entity> m_player;

	void init(const std::string& configPath);
	void setPaused(bool paused);

	void sMovement(); // System : Entity movement/position update;
	void sUserInput();
	void sLifeSpan();
	void sRender();
	void sEnemySpawner();
	void sCollision();

	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemy(std::shared_ptr<Entity> entity);
	void spawnBullet(std::shared_ptr<Entity>, const Vec2 & mouse_pos);
	void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:
	Game(std::string& configPath);

	void run();
};
#endif
