#pragma once

#include "manyakSDL.hpp"

class GameObject {

public:
	void render();
	virtual void update(float delta) = 0;
	
	virtual ~GameObject();
protected:

	SDL_Texture* mTexture;
	SDL_Rect mRenderBox;
	SDL_Rect mSpriteClip;
	bool isClipped;
};