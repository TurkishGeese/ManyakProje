#include "emptyComponentManager.hpp"


Component* EmptyComponentManager::addComponent(Entity entity)
{
	(void)entity;
	return nullptr;
}