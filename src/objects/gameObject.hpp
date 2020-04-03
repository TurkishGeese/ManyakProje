#pragma once

#include "manyakSDL.hpp"
#include "action.hpp"

class GameObject {

public:
	void render();
	virtual void update(float delta) = 0;
	virtual void input(Action action) = 0;
	
	virtual ~GameObject();
protected:

	SDL_Texture* mTexture;
	SDL_Rect mRenderBox;
	SDL_Rect mSpriteClip;
	bool isClipped;
};