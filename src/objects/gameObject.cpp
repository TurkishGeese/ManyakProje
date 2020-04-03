#include "gameObject.hpp"
#include "../renderer.hpp"

void GameObject::render() {
	if (isClipped)
		Renderer::render(mTexture, &mRenderBox, &mSpriteClip);
	else 
		Renderer::render(mTexture, &mRenderBox);
}

GameObject::~GameObject() {
    if (mTexture != nullptr)
        SDL_DestroyTexture(mTexture);
}