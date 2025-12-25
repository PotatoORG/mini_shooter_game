#include "Entity.h"
#include "EntityManager.h"

EntityManager::EntityManager() {}

std::shared_ptr<Entity> EntityManager::addEntity(const CTag& tag){
	auto entity = std::make_shared<Entity>(m_totalEntities, tag);
	m_entities.push_back(entity);
	m_entityMap[tag].push_back(entity);

	return entity;
}

EntityVec& EntityManager::getEntities(){
	return m_entities;
}

EntityVec& EntityManager::getEntities(CTag tag){
	return m_entityMap[tag];
}

// update function is supposed to be called by the game at start of each frame to update the added entities
void EntityManager::update(){
	for (auto e : m_toAdd){
		m_entities.push_back(e);
		m_entityMap[e->tag()].push_back(e);
	}
	m_toAdd.clear();
}

