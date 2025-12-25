#include "Game.h"

#include <iostream>

Game::Game(const std::string& configPath){
	init(configPath);
}

void Game::init(const std::string& configPath){
	// config reading to be done;

	m_window.create(sf::VideoMode(1280, 720), "Polygon Shoots Polygon");
	m_window.setFramerateLimit(60);

	spawnPlayer();
};

void Game::run(){
	// add pause functionality here;;
	//
	 while (m_running){
		 m_entityManager.update();

		 if (!m_paused){
		 	sEnemySpawner();
			sUserInput();
			sMovement();
			sCollision();
		 }
		 sRender();

		 m_currentFrame++;
	 }
}

void Game::setPaused(){
	;
}

// initializes the player entity, its transform, shape;
void Game::spawnPlayer(){
	auto entity = m_entityManager.addEntity(player);
	// to be changed to load the propertied from config.
	entity->cTransform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 0.0f);

	entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 255, 255), 4.0f);
	entity->cInput = std::make_shared<CInput>();

	m_player = entity; // Should not be allowed in ECS, but we are just doing it for some convinience.
}

// intitializes an enemy entity when called
void Game::spawnEnemy(){
	auto entity = m_entityManager.addEntity(enemy);

	float ex = rand() % m_window.getSize().x;
	float ey = rand() % m_window.getSize().y;
	float eAngle = rand() % 360;

	entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(0, 0), eAngle);

	entity->cShape = std::make_shared<CShape>(16.0f, 3, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);
	std::cout << "Enemy spawned at (" << ex << ", " << ey << ")\n";

	m_lastEnemySpawnedTime = m_currentFrame;
}

void Game::spawnSmallEnemy(std::shared_ptr<Entity> entity){
	;
}

void Game::spawnBullet(std::shared_ptr<Entity>, const Vec2 & mouse_pos){
	;
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity){
	;
}

void Game::sEnemySpawner(){
	// will decide when to spawn an enemy and call the spawnEnemy function to spawn the enemy.
	size_t spawnInterval = 50; // Number of frames after to spawn an enemy, temparory var until SI implemented.
	if (spawnInterval <= m_currentFrame - m_lastEnemySpawnedTime){
		spawnEnemy();
	}
}

void Game::sMovement(){
	//Player movement;
	m_player->cTransform->velocity.y = 0;
	m_player->cTransform->velocity.x = 0;

	if (m_player->cInput->up){
		m_player->cTransform->velocity.y = -5;
	}
	if (m_player->cInput->down){
		m_player->cTransform->velocity.y = 5;
	}
	if (m_player->cInput->left){
		m_player->cTransform->velocity.x = -5;
	}
	if (m_player->cInput->right){
		m_player->cTransform->velocity.x = 5;
	}
	auto entities = m_entityManager.getEntities();
	for (auto& e : entities){
		e->cTransform->pos.x += e->cTransform->velocity.x;
		e->cTransform->pos.y += e->cTransform->velocity.y;

		e->cTransform->angle += 1.0f;
	}
}

void Game::sCollision(){
}

void Game::sUserInput(){
	sf::Event event;
	while (m_window.pollEvent(event)){
		if (event.type == sf::Event::Closed){
			m_running = false;
		}

		if (event.type == sf::Event::KeyPressed){
			switch (event.key.code){
				case sf::Keyboard::W:
					std::cout << "W pressed\n";
					m_player->cInput->up = true;
					break;
				case sf::Keyboard::A:
					std::cout << "A pressed\n";
					m_player->cInput->left = true;
					break;
				case sf::Keyboard::S:
					std::cout << "S pressed\n";
					m_player->cInput->down = true;
					break;
				case sf::Keyboard::D:
					std::cout << "D pressed\n";
					m_player->cInput->right = true;
					break;
				case sf::Keyboard::K:
					std::cout << "K pressed\n";
					m_player->cInput->shoot = true;
					break;
				case sf::Keyboard::J:
					std::cout << "J pressed\n";
					m_player->cInput->special = true;
					break;
			}
		}

		if (event.type == sf::Event::KeyReleased){
			switch (event.key.code){
				case sf::Keyboard::W:
					std::cout << "W released\n";
					m_player->cInput->up = false;
					break;
				case sf::Keyboard::A:
					std::cout << "A released\n";
					m_player->cInput->left = false;
					break;
				case sf::Keyboard::S:
					std::cout << "S released\n";
					m_player->cInput->down = false;
					break;
				case sf::Keyboard::D:
					std::cout << "D released\n";
					m_player->cInput->right = false;
					break;
				case sf::Keyboard::K:
					std::cout << "K released\n";
					m_player->cInput->shoot = false;
					break;
				case sf::Keyboard::J:
					std::cout << "J released\n";
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
					std::cout << "Mouse Left Clicked\n";
					m_player->cInput->shoot = true;
					break;
				case sf::Mouse::Right:
					std::cout << "Mouse Right Clicked\n";
					m_player->cInput->shoot = true;
					break;
			}
		}

		if (event.type == sf::Event::MouseButtonReleased){
			switch (event.mouseButton.button){
				case sf::Mouse::Left:
					std::cout << "Mouse Left Released\n";
					m_player->cInput->shoot = false;
					break;
				case sf::Mouse::Right:
					std::cout << "Mouse Right Released\n";
					m_player->cInput->shoot = false;
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
	m_window.display();
}
