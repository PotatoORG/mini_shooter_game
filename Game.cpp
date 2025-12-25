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
		 m_entityManager.update();

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

void Game::setPaused(){
	;
}

void Game::spawnPlayer(){
	auto entity = m_entityManager.addEntity(player);
	// to be changed to load the propertied from config.
	entity->cTransform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 0.0f);

	entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 255, 255), 4.0f);

	entity->cInput = std::make_shared<CInput>();

	m_player = entity;
}

void Game::spawnEnemy(){
	auto entity = m_entityManager.addEntity(enemy);

	float ex = rand() % m_window.getSize().x;
	float ey = rand() % m_window.getSize().y;

	entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(0, 0), 0.0f);

	entity->cShape = std::make_shared<CShape>(16.0f, 3, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);

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
}

void Game::sMovement(){
	;
}

void Game::sCollision(){
}

void Game::sUserInput(){
}

void Game::sRender(){
}
