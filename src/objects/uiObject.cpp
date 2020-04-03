#include "uiObject.hpp"

#include "renderer.hpp"

UIObject::~UIObject() {
    if (mTexture != nullptr)
        SDL_DestroyTexture(mTexture);
}

void UIObject::render() {
	Renderer::render(mTexture, &mRenderBox);
}