#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"

typedef std::vector<Entity> EntityVec;
typedef std::map<CTag, std::vector> EntityMap;

class EntityManager{
	EntityVec m_entities;
	EntityVec m_toAdd;
	EntityMap m_entityMap;
	size_t	  m_totalEntities;

public:
	EntityManager();
	std::shared_ptr<Entity> addEntity();
	EntityVec getEntities();
	EntityVec getEntities(Ctag tag);
};

#endif
