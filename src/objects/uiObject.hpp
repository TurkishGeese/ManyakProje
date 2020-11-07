#pragma once

#include "manyakSDL.hpp"
#include "asset.hpp"
#include "vec2.hpp"
#include "entity.hpp"

class UIObject {

public:
	// TODO Just by logic, UIObjects will have children. This object should have children and should render them as well.
	virtual void render();
	virtual void update();

	virtual ~UIObject();
protected:

	Asset* mAsset;
	Vec2 mPosition;
	Vec2 mRenderSize;
};

namespace UI
{
	Entity createText(std::string text, Vec2 position, SDL_Color color);
	Entity createButton(void (*func)(), std::string text, Vec2 position, Vec2 size);
}
