#include "texture.hpp"

#include "renderer.hpp"

#include <assert.h>
#include "logger.hpp"

Texture::Texture(std::string path, Vec2 clipGrid, int clips) {
	isClipped = clips != 1;
	mTexture = Renderer::loadTextureFromPath(path, mTextureSize);
	mClipGrid = clipGrid;
	mClipUnit = { mTextureSize.x / clipGrid.x, mTextureSize.y / clipGrid.y };
	mClips = clips;
}

Texture::Texture(SDL_Surface *textSurface){
	mTexture = Renderer::textureFromSurface(textSurface);
	mClipGrid = { 1, 1 };
	mClipUnit = { 0, 0 };
	mClips = 1;
}

Texture::~Texture() {
	if (mTexture != nullptr)
		SDL_DestroyTexture(mTexture);
}

void Texture::render(Vec2 position, Vec2 renderSize) {
	SDL_Rect renderPos = { (int)position.x, (int)position.y, (int)renderSize.x, (int)renderSize.y };
	Renderer::render(mTexture, &renderPos);
}

bool Texture::render(Vec2 position, Vec2 renderSize, int clip) {
	assert(isClipped && "Trying to clip an unclipped texture!");

	SDL_Rect renderPos = { (int)position.x, (int)position.y, (int)renderSize.x, (int)renderSize.y };

	bool ret = (clip >= mClips);
	clip = clip % mClips;
	int x = clip % (int)mClipGrid.x;
	int y = clip / (int)mClipGrid.x;
	SDL_Rect clipRect = { int(x * mClipUnit.x), int(y * mClipUnit.y), int(mClipUnit.x), int(mClipUnit.y) };

	Renderer::render(mTexture, &renderPos, &clipRect);
	return ret;
}

