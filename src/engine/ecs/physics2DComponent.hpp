#pragma once

#include "component.hpp"

class b2Body;

struct Physics2DComponent : Component
{
	b2Body* Body = nullptr;
	Vec2 size;
};