#pragma once

#include "manyakSDL.hpp"
#include "manyakSDLttf.hpp"

class Renderer {

public:
	static void initialize(SDL_Renderer* sdlRenderer);
	static void quit();

	// If the rendered texture doesn't need to be clipped then clip is nullptr
	static void render(SDL_Texture* texture, SDL_Rect* pos, SDL_Rect* clip = nullptr);

	static Renderer* sIntance;
private:

	Renderer(SDL_Renderer* sdlRenderer);

	SDL_Renderer* mSdlRenderer;

	void internalRender(SDL_Texture* texture, SDL_Rect* pos, SDL_Rect* clip);
};