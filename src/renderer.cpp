#include "renderer.hpp"

Renderer* Renderer::sIntance = nullptr;

void Renderer::initialize(SDL_Renderer* sdlRenderer) {
	sIntance = new Renderer(sdlRenderer);
}

void Renderer::quit() {
	delete sIntance;
}

void Renderer::render(SDL_Texture* texture, SDL_Rect* pos, SDL_Rect* clip) {
	sIntance->internalRender(texture, pos, clip);
}

Renderer::Renderer(SDL_Renderer* sdlRenderer) {
	mSdlRenderer = sdlRenderer;
}

void Renderer::internalRender(SDL_Texture* texture, SDL_Rect* pos, SDL_Rect* clip) {
	SDL_RenderCopy(mSdlRenderer, texture, clip, pos);
}