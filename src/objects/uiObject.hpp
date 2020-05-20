#pragma once

#include "manyakSDL.hpp"
#include "texture.hpp"
#include "vec2.hpp"

class UIObject {

public:
	// TODO Just by logic, UIObjects will have children. This object should have children and should render them as well.
	virtual void render();
	virtual void update(float delta);

	virtual ~UIObject();
protected:

	Texture* mTexture;
	Vec2 mPosition;
	SDL_Texture* mSDL_Texture;
	SDL_Rect mRenderBox;
};