#include "Entity.h"

Entity::Entity(const size_t id, const CTag tag)
	: m_id(id), m_tag(tag) {}

size_t id() const{
	return m_id;
}

const CTag& tag() const{
	return m_tag;
}

bool isAlive() const{
	return m_alive;
}

void destroy(){
	m_alive = false;
}
