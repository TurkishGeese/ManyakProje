#pragma once

#include "manyakSDL.hpp"

class UIObject {

public:
	// TODO Just by logic, UIObjects will have children. This object should have children and should render them as well.
	void render();

	virtual ~UIObject();
protected:

	SDL_Texture* mTexture;
	SDL_Rect mRenderBox;
};