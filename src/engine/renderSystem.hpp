#pragma once

#include "system.hpp"

class RenderSystem : System
{
public:
	virtual void update();
	virtual void finalizeEntity(Entity entity);

};