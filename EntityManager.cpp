#include "Entity.h"

EntityManager::EntityManager() {}

std::shared_ptr<Entity> EntityManager::addEntity(const Ctag& tag){
	auto entity = std::make_shared<Entity>(m_totalEntities, tag);
	m_entities.pushback(entity);
	m_entityMap[tag].pushback(entity);

	return entity;
}

EntityVec EntityManager::getEntities();
EntityVec EntityManager::getEntities(Ctag tag);

// update function is supposed to be called by the game at start of each frame to update the added entities
void EntityManager::update(){
	for (auto& e : m_toAdd){
		m_entities.pushback(e);
		m_entityMap[e->m_tag].pushback(e);
	}
	m_toAdd.clear();
}

