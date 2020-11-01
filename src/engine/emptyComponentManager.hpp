#pragma once

#include "componentManager.hpp"

class EmptyComponentManager : ComponentManager<Component>
{
public:
	virtual Component* addComponent(Entity entity);
};