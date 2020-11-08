#pragma once

#include "system.hpp"

class RenderSystem : System
{
public:
	virtual void update(float delta);
	virtual void finalizeEntity(Entity entity);

};