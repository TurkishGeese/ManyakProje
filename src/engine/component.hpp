#pragma once

#include "entity.hpp"

class Component
{
public:
	Component(Entity entity);

protected:

	Entity m_entity;
};