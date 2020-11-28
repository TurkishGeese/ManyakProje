#pragma once

#include "system.hpp"

class InputSystem : System
{
public:
	virtual void update(float delta);
	virtual void finalizeEntity(Entity entity);

};