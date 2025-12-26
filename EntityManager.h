#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include <memory>

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<CTag, EntityVec> EntityMap;

class EntityManager{
	EntityVec m_entities;
	EntityVec m_toAdd;
	EntityMap m_entityMap;
	size_t	  m_totalEntities = 0;

public:
	EntityManager();
	std::shared_ptr<Entity> addEntity(const CTag& tag);
	EntityVec& getEntities();
	EntityVec& getEntities(CTag tag);
	void	   removeDeadEntities();

	void update();
};

#endif
