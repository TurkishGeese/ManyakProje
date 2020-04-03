#include "renderer.hpp"

#include "logger.hpp"
#include "manyakSDLimage.hpp"

Renderer* Renderer::sInstance = nullptr;

void Renderer::initialize(SDL_Renderer* sdlRenderer) {
	sInstance = new Renderer(sdlRenderer);
}

void Renderer::quit() {
	delete sInstance;
}

void Renderer::render(SDL_Texture* texture, SDL_Rect* pos, SDL_Rect* clip) {
	sInstance->internalRender(texture, pos, clip);
}

SDL_Texture* Renderer::textureFromSurface(SDL_Surface* surface) {
	return sInstance->internalTextureFromSurface(surface);
}

SDL_Texture* Renderer::loadTextureFromPath(std::string path) {
	return sInstance->internalLoadTextureFromPath(path);
}

Renderer::Renderer(SDL_Renderer* sdlRenderer) {
	mSdlRenderer = sdlRenderer;
}

void Renderer::internalRender(SDL_Texture* texture, SDL_Rect* pos, SDL_Rect* clip) {
	SDL_RenderCopy(mSdlRenderer, texture, clip, pos);
}

SDL_Texture* Renderer::internalTextureFromSurface(SDL_Surface* surface) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(mSdlRenderer, surface);
    if (texture == nullptr) {
        Logger::logSdlError("Could not create texture from text surface!");
    }
	return texture;
}

SDL_Texture* Renderer::internalLoadTextureFromPath(std::string path) {
    SDL_Texture *newTexture = nullptr;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        Logger::logSdlImageError("Could not load image!");
        return nullptr;
    }
    newTexture = SDL_CreateTextureFromSurface(mSdlRenderer, loadedSurface);
    if (newTexture == nullptr) {
        Logger::logSdlImageError("Could not create texture from image!");
    }
    SDL_FreeSurface(loadedSurface);
	return newTexture;
}