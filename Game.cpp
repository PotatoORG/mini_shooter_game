#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

#include "Game.h"


Game::Game(const std::string& configPath){
	init(configPath);
}

void Game::init(const std::string& configPath){
	// config reading to be done;
	std::ifstream conf("./config.txt");
	std::string temp;

	while (conf >> temp){
		if (temp == "Window"){
			conf >> m_windowConfig.W >> m_windowConfig.H >> m_windowConfig.FL >> m_windowConfig.FS;
			std::cout << "Window config read\n";
		}
		if (temp == "Font"){
			conf >> m_fontConfig.F >> m_fontConfig.S >> m_fontConfig.R >> m_fontConfig.G >> m_fontConfig.B;
			std::cout << "Font config read\n";
		}
		if (temp == "Player"){
			conf >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S >> m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB >> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB >> m_playerConfig.OT >> m_playerConfig.V;
			std::cout << "Player config read\n";
		}
		if (temp == "Enemy"){
			conf >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX >> m_enemyConfig.OR >> m_enemyConfig.OG >> m_enemyConfig.OB >> m_enemyConfig.OT >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX >> m_enemyConfig.L >> m_enemyConfig.SI;
			std::cout << "Enemy config read\n";
		}
		if (temp == "Bullet"){
			conf >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB >> m_bulletConfig.OT >> m_bulletConfig.V >> m_bulletConfig.L ;
			std::cout << "Bullet config read\n";
		}

	}

	if (!m_font.loadFromFile(m_fontConfig.F)){
		std::cerr << "Font file : " << m_fontConfig.F << " not found.\n";
		std::exit(0);
	}
	m_text.setFont(m_font);
	m_text.setString("Score -_- '");
	m_window.create(sf::VideoMode(m_windowConfig.W, m_windowConfig.H), "Polygon Shoots Polygon");
	m_window.setFramerateLimit(m_windowConfig.FL);


	m_bulletConfig.S = 10.0f;
	spawnPlayer();
};

void Game::run(){
	// add pause functionality here;;

	std::cout << "SI = " << m_enemyConfig.SI << "\n";
	 while (m_running){
		 sLifeSpan();
		 m_entityManager.removeDeadEntities();
		 m_entityManager.update();

		 if (!m_paused){
		 	sEnemySpawner();
			sUserInput();
			sMovement();
			sAttack();
			sCollision();
		 }
		 sRender();

		 m_currentFrame++;
	 }
}

void Game::setPaused(){
	m_paused = true;
}

// initializes the player entity, its transform, shape;
void Game::spawnPlayer(){
	auto entity = m_entityManager.addEntity(player);

	// position where the player will be spawned
	auto cx = m_window.getSize().x/2;
	auto cy = m_window.getSize().y/2;

	Vec2 velocity = {0, 0}; // Random init. Doesn't matters;

	entity->cTransform = std::make_shared<CTransform>(Vec2(cx, cy), velocity, 0.0f);

	auto fillColor = sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB);
	auto outlineColor = sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB);

	entity->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.CR, fillColor, outlineColor, m_playerConfig.OT);

	entity->cInput = std::make_shared<CInput>();

	m_player = entity; // Should not be allowed in ECS, but we are just doing it for some convinience.
}

// intitializes an enemy entity when called
void Game::spawnEnemy(){
	auto entity = m_entityManager.addEntity(enemy);

	float 	ex, ey;
	auto 	outlineColor = sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB);
	auto 	fillColor 	 = sf::Color(rand()%255, rand()%255, rand()%255); // Random Color
	int 	vertices 	 = m_enemyConfig.VMIN + rand() % (int)(m_enemyConfig.VMAX - m_enemyConfig.VMIN);
	auto 	speed 		 = m_enemyConfig.SMIN + rand() % (int)(m_enemyConfig.SMAX - m_enemyConfig.SMIN);
	float 	theta 		 = rand() % 360;

	entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR, vertices, fillColor, outlineColor, m_enemyConfig.OT);

	Vec2 velocity = {std::cos(theta), std::sin(theta)};
	velocity *= speed;

	float 	minDistance  = m_player->cShape->polygon.getRadius() + entity->cShape->polygon.getRadius() + 10; // Minimum allowed initial separation between player and spawned enemy.
	do{
		ex = rand() % (int)(m_window.getSize().x - 2*entity->cShape->polygon.getRadius());
		ey = rand() % (int)(m_window.getSize().y - 2*entity->cShape->polygon.getRadius());
	} while (Vec2(ex, ey).distance(m_player->cTransform->pos) <= minDistance);

	entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), velocity, theta);

	std::cout << "Enemy spawned at (" << ex << ", " << ey << ")\n";
	m_lastEnemySpawnedTime = m_currentFrame;
}

void Game::spawnSmallEnemy(std::shared_ptr<Entity> entity){
	;
}

void Game::spawnBullet(const Vec2 & mousePos){
	auto b = m_entityManager.addEntity(bullet);
	//b->cTransform->pos = m_player->cTransform->pos;
	b->cTransform = std::make_shared<CTransform>(m_player->cTransform->pos, Vec2(0, 0), 0.0f);

	auto fillColor = sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB);
	auto outlineColor = sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB);

	b->cShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.V, fillColor, outlineColor, m_bulletConfig.OT);

	float speed = m_bulletConfig.S;

	auto dy = mousePos.y - b->cTransform->pos.y;
	auto dx = mousePos.x - b->cTransform->pos.x;

	auto theta = std::atan2(dy, dx);

	b->cTransform->velocity = {std::cos(theta), std::sin(theta)};
	b->cTransform->velocity *= speed;

	b->cLifeSpan = std::make_shared<CLifeSpan>(m_bulletConfig.L);
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity){
	;
}

void Game::resetGame(){
	m_player->cTransform->pos = {200.0f, 200.0f};
	m_score = 0;
	auto& enemies = m_entityManager.getEntities(enemy);
	for (auto& enemy : enemies){
		enemy->destroy();
	}

	auto& bullets = m_entityManager.getEntities(bullet);
	for (auto& bullet : bullets){
		bullet->destroy();
	}
}

void Game::sEnemySpawner(){
	// will decide when to spawn an enemy and call the spawnEnemy function to spawn the enemy.
	//size_t spawnInterval = 100; // Number of frames after to spawn an enemy, temparory var until SI implemented.
	if (m_enemyConfig.SI <= m_currentFrame - m_lastEnemySpawnedTime){
		std::cout << "frame : " << m_currentFrame << ", last enemy spawned on : " << m_lastEnemySpawnedTime << ", SI :" << m_enemyConfig.SI << "\n";
		spawnEnemy();
	}
	/*
	static bool spawned = false;
	if (!spawned){ spawnEnemy(); spawnEnemy(); spawned = true;}
	*/

}

void Game::sMovement(){
	//Player movement;
	m_player->cTransform->velocity.y = 0;
	m_player->cTransform->velocity.x = 0;

	if (m_player->cInput->up){
		m_player->cTransform->velocity.y = -m_playerConfig.S;
	}
	if (m_player->cInput->down){
		m_player->cTransform->velocity.y = m_playerConfig.S;
	}
	if (m_player->cInput->left){
		m_player->cTransform->velocity.x = -m_playerConfig.S;
	}
	if (m_player->cInput->right){
		m_player->cTransform->velocity.x = m_playerConfig.S;
	}

	auto entities = m_entityManager.getEntities();
	for (auto& e : entities){
		e->cTransform->pos.x += e->cTransform->velocity.x;
		e->cTransform->pos.y += e->cTransform->velocity.y;

		e->cTransform->angle += 2.0f;
	}
}

// Checks user input and shoots bullets or do special attack accordingly
void Game::sAttack(){
	if (m_player->cInput->shoot){
		spawnBullet(m_player->cInput->aim);
	}
}


// This will detect player's collision with any enemy or bullet's collision with any enemy and call the required functions to proceed.
// And collision of enemies with walls of window and will deflect them back if they do so
void Game::sCollision(){

	auto enemies = m_entityManager.getEntities(enemy);
	auto bullets = m_entityManager.getEntities(bullet);

	float separation;

	// Player - Enemy collision checker
	for (auto& enemy : enemies){

		separation = m_player->cTransform->pos.distance(enemy->cTransform->pos);

		if (separation <= (m_player->cShape->polygon.getRadius() + enemy->cShape->polygon.getRadius())){
			resetGame(); // resets score, position of player and enemies
			return;
		}
	}

	enemies = m_entityManager.getEntities(enemy); // since reset_game function may cause vector to reallocate.

	// Bullet - enemy collision checker
	for (auto& bullet : bullets){
		for (auto& enemy : enemies){
			separation = bullet->cTransform->pos.distance(enemy->cTransform->pos);
			if (separation <= (bullet->cShape->polygon.getRadius() + enemy->cShape->polygon.getRadius())){
				m_score++;
				bullet->destroy();
				enemy->destroy();
			}
		}
	}

	// Enemy wall collision
	for (auto& enemy : enemies){
		auto radius = m_enemyConfig.SR;
		if (enemy->cTransform->pos.x < radius){
			enemy->cTransform->velocity.x *= -1;
		}
		if (enemy->cTransform->pos.x > m_window.getSize().x - radius){
			enemy->cTransform->velocity.x *= -1;
		}
		if (enemy->cTransform->pos.y < radius){
			enemy->cTransform->velocity.y *= -1;
		}
		if (enemy->cTransform->pos.y > m_window.getSize().y - radius){
			enemy->cTransform->velocity.y *= -1;
		}

	}

	auto radius = m_player->cShape->polygon.getRadius();
	if (m_player->cTransform->pos.x < radius){
		m_player->cTransform->pos.x = radius;
	}
	if (m_player->cTransform->pos.x > m_window.getSize().x - radius){
		m_player->cTransform->pos.x = m_window.getSize().x - radius;
	}
	if (m_player->cTransform->pos.y < radius){
		m_player->cTransform->pos.y = radius;
	}
	if (m_player->cTransform->pos.y > m_window.getSize().y - radius){
		m_player->cTransform->pos.y = m_window.getSize().y - radius;
	}
}

// This system is suppose to take user input and convert it into the game interface variables, player's cInput components.
void Game::sUserInput(){
	sf::Event event;
	while (m_window.pollEvent(event)){
		if (event.type == sf::Event::Closed){
			m_running = false;
		}

		if (event.type == sf::Event::KeyPressed){
			switch (event.key.code){
				case sf::Keyboard::W:
					//std::cout << "W pressed\n";
					m_player->cInput->up = true;
					break;
				case sf::Keyboard::A:
					//std::cout << "A pressed\n";
					m_player->cInput->left = true;
					break;
				case sf::Keyboard::S:
					//std::cout << "S pressed\n";
					m_player->cInput->down = true;
					break;
				case sf::Keyboard::D:
					//std::cout << "D pressed\n";
					m_player->cInput->right = true;
					break;
				case sf::Keyboard::K:
					//std::cout << "K pressed\n";
					m_player->cInput->shoot = true;
					break;
				case sf::Keyboard::J:
					//std::cout << "J pressed\n";
					m_player->cInput->special = true;
					break;
			}
		}

		if (event.type == sf::Event::KeyReleased){
			switch (event.key.code){
				case sf::Keyboard::W:
					//std::cout << "W released\n";
					m_player->cInput->up = false;
					break;
				case sf::Keyboard::A:
					//std::cout << "A released\n";
					m_player->cInput->left = false;
					break;
				case sf::Keyboard::S:
					//std::cout << "S released\n";
					m_player->cInput->down = false;
					break;
				case sf::Keyboard::D:
					//std::cout << "D released\n";
					m_player->cInput->right = false;
					break;
				case sf::Keyboard::K:
					//std::cout << "K released\n";
					m_player->cInput->shoot = false;
					break;
				case sf::Keyboard::J:
					//std::cout << "J released\n";
					m_player->cInput->special = false;
					break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed){
			m_player->cInput->aim.x = event.mouseButton.x;
			m_player->cInput->aim.y = event.mouseButton.y;
			std::cout << "Clicked at (" << m_player->cInput->aim.x << ", " << event.mouseButton.y << ")\n";

			switch (event.mouseButton.button){
				case sf::Mouse::Left:
					//std::cout << "Mouse Left Clicked\n";
					m_player->cInput->shoot = true;
					break;
				case sf::Mouse::Right:
					//std::cout << "Mouse Right Clicked\n";
					m_player->cInput->special = true;
					break;
			}
		}

		if (event.type == sf::Event::MouseButtonReleased){
			switch (event.mouseButton.button){
				case sf::Mouse::Left:
					//std::cout << "Mouse Left Released\n";
					m_player->cInput->shoot = false;
					break;
				case sf::Mouse::Right:
					//std::cout << "Mouse Right Released\n";
					m_player->cInput->special = false;
					break;
			}

		}
	}
}

void Game::sRender(){
	m_window.clear();
	auto entities = m_entityManager.getEntities();
	for (auto& e : entities){
		e->cShape->polygon.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

		
		e->cShape->polygon.setRotation(e->cTransform->angle);
		m_window.draw(e->cShape->polygon);
	}

	m_text.setString("Score : " + std::to_string(m_score));
	m_window.draw(m_text);

	m_window.display();
}

void Game::sLifeSpan(){
	auto bullets = m_entityManager.getEntities(bullet);
	for (auto& bullet : bullets){
		if(!bullet->cLifeSpan->remaining--){
			bullet->destroy();
		}
	}
}
