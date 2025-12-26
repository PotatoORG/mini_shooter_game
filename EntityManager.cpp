#include <iostream>

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

void EntityManager::removeDeadEntities(){
	for (auto it = m_entities.begin(); it != m_entities.end();){
		if (!(*it)->isAlive()){
			auto idToRemove = (*it)->id();
			auto entityTag = (*it)->tag();
			auto entity = *it;

			it = m_entities.erase(it);

			m_entityMap[entityTag].erase(find(m_entityMap[entityTag].begin(), m_entityMap[entityTag].begin(), entity));
			//m_entityMap[entityTag].erase(entity);
		} else {
			it++;
		}
	}
	std::cout << "Number of entities left: " << m_entities.size() << "\n";
}

