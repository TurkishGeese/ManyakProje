#pragma once

#include "manyakSDL.hpp"
#include "asset.hpp"
#include "vec2.hpp"
#include "entity.hpp"

namespace UI
{
	Entity createText(std::string text, Vec2 position, SDL_Color color);
	Entity createButton(void (*onClick)(), std::string text, Vec2 position, Vec2 size);
}
