#include "texture.hpp"

#include "renderer.hpp"

Texture::Texture(std::string path, Vec2 size) {
	isClipped = true;
	mTexture = Renderer::loadTextureFromPath(path, mTextureSize);
	mRenderSize = size;
}

Texture::Texture(std::string path, Vec2 size, SDL_Rect clip) {
	isClipped = true;
	mTexture = Renderer::loadTextureFromPath(path, mTextureSize);
	mRenderSize = size;
	mClip = clip;
}

Texture::~Texture() {
	if (mTexture != nullptr)
		SDL_DestroyTexture(mTexture);
}

void Texture::render(Vec2 position) {
	if (isClipped) {
		SDL_Rect renderPos = { (int)position.x, (int)position.y, (int)mRenderSize.x, (int)mRenderSize.y };
		Renderer::render(mTexture, &renderPos, &mClip);
	}
	else {
		SDL_Rect renderPos = { (int)position.x, (int)position.y, (int)mRenderSize.x, (int)mRenderSize.y };
		Renderer::render(mTexture, &renderPos);
	}
}