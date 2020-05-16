#pragma once

#include "vec2.hpp"
#include "manyakSDL.hpp"

#include <string>

class Texture {

public:
	Texture(std::string path, Vec2 size);
	Texture(std::string path, Vec2 size, SDL_Rect clip); // TODO better way to handle clips in textures?
	~Texture();

	void render(Vec2 position);
private:
	SDL_Rect mClip;
	Vec2 mRenderSize;
	Vec2 mTextureSize;
	SDL_Texture* mTexture;
	bool isClipped;
};