#include "Game.h"

#include <iostream>

Game::Game(const std::string& configPath){
	init(configPath);
}

void Game::init(const std::string& configPath){
	// config reading to be done;

	m_window.create(sf::VideoMode(1280, 720), "Polygon Shoots polygon");
	m_window.setFramerateLimit(60);

	spawnPlayer();
};

void Game::run(){
	// add pause functionality here;;
	//
	 while (m_running){
		 m_entities.update();

		 if (!m_paused){
		 	sEnemySpawner();
			sMovement();
			sCollision();
			sUserInput();
		 }
		 sRender();

		 m_currentFrame++;
	 }
}

void Game::spawnPlayer(){
	auto entity = m_entities.addEntity(player);
	// to be changed to load the propertied from config.
	entity->cTransform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 0.0f);

	entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color::(10, 10, 10), sf::Color(255, 255, 255), 4.0f);

	entity->cInput = std::make_shared<CInput>();

	m_player = entity;
}

void Game::spawnEnemy(){
	auto entity = std::make_shared<Entity>(enemy);

	float ex = rand() % m_window.getSize().x;
	float ey = rand() % m_window.getSize().y;

	entity->cTransform = std::make_shared<CTransform>({ex, ey}, {0, 0}, 0.0f);

	entity->cShape = std::make_shared<CShape>(16.0f, 3, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);

	m_lastEnemySpawnedTime = m_currentFrame;
}
