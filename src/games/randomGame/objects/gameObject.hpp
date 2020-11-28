#pragma once

#include "entity.hpp"
#include "inputType.hpp"
#include "vec2.hpp"

class InputConfiguration;

namespace Game
{
	Entity createPlayer(InputType inputType, InputConfiguration* config);
	Entity createWall(Vec2 pos, Vec2 size);
}