#include "texture.hpp"

#include "renderer.hpp"

#include <assert.h>
#include "logger.hpp"

Texture::Texture(std::string path, Vec2 clipGrid, int clips) {
	mTexture = Renderer::loadTextureFromPath(path, mTextureSize);
	mClipGrid = clipGrid;
	mClipUnit = { mTextureSize.x / clipGrid.x, mTextureSize.y / clipGrid.y };
	mClips = clips;
}

Texture::Texture(SDL_Surface *textSurface){
	mTexture = Renderer::textureFromSurface(textSurface);
	mTextureSize = { (float)textSurface->w, (float)textSurface->h };
	mClipGrid = { 1, 1 };
	mClipUnit = mTextureSize;
	mClips = 1;
}

Texture::~Texture() {
	if (mTexture != nullptr)
		SDL_DestroyTexture(mTexture);
}

bool Texture::render(Vec2 position, Vec2 renderSize, int clip) {
	SDL_Rect renderPos = { (int)position.x, (int)position.y, (int)renderSize.x, (int)renderSize.y };

	bool ret = (clip >= mClips);
	clip = clip % mClips;
	int x = clip % (int)mClipGrid.x;
	int y = clip / (int)mClipGrid.x;
	SDL_Rect clipRect = { int(x * mClipUnit.x), int(y * mClipUnit.y), int(mClipUnit.x), int(mClipUnit.y) };

	Renderer::render(mTexture, &renderPos, &clipRect);
	return ret;
}

Vec2 Texture::getTextureSize()
{
	return mTextureSize;
}
