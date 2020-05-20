#include "uiObject.hpp"

#include "renderer.hpp"

UIObject::~UIObject() {
    if (mTexture != nullptr)
        SDL_DestroyTexture(mSDL_Texture);
    if (mSDL_Texture != nullptr)
        SDL_DestroyTexture(mSDL_Texture);
}

void UIObject::render() {
	Renderer::render(mSDL_Texture, &mRenderBox);
}

void UIObject::update(){}