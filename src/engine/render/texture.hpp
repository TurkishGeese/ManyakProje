#pragma once

#include "vec2.hpp"
#include "manyakSDL.hpp"

#include <string>

class Texture {

public:
	Texture(std::string path, Vec2 clipGrid, int clips);
	Texture(SDL_Surface *textSurface);
	~Texture();

	bool render(Vec2 position, Vec2 renderSize, int clip);
	Vec2 getTextureSize();

private:
	int mClips;
	Vec2 mClipGrid;
	Vec2 mClipUnit;
	Vec2 mTextureSize;
	SDL_Texture* mTexture;
};