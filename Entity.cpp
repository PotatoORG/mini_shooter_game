#include "Entity.h"

Entity::Entity(const size_t id, const CTag tag)
	: m_id(id), m_tag(tag) {}

size_t Entity::id() const{
	return m_id;
}

const CTag& Entity::tag() const{
	return m_tag;
}

bool Entity::isAlive() const{
	return m_alive;
}

void Entity::destroy(){
	m_alive = false;
}
