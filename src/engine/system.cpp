#include "system.hpp"

void System::removeEntity(Entity entity)
{
	m_entities.erase(entity);
}