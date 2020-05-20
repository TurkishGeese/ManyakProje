#pragma once

#include "manyakSDL.hpp"
#include "texture.hpp"
#include "vec2.hpp"

class UIObject {

public:
	// TODO Just by logic, UIObjects will have children. This object should have children and should render them as well.
	virtual void render();
	virtual void update();

	virtual ~UIObject();
protected:

	Texture* mTexture = nullptr;
	Vec2 mPosition;
	SDL_Texture* mSDL_Texture = nullptr;
	SDL_Rect mRenderBox;
};