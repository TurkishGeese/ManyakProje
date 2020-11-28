#pragma once

#include <unordered_set>
#include "entity.hpp"

class System
{
public:
	virtual ~System() {};
	
	virtual void update(float delta) = 0;
	virtual void finalizeEntity(Entity entity) = 0;
	virtual void removeEntity(Entity entity);

protected:
	std::unordered_set<Entity> m_entities;
};