#pragma once

#include "system.hpp"

class UIInputSystem : System
{
public:
	virtual void update(float delta);
	virtual void finalizeEntity(Entity entity);

};