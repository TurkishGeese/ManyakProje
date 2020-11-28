#pragma once

#include "component.hpp"
#include "vec2.hpp"

struct TransformComponent : Component
{
	Vec2 m_transform;
};