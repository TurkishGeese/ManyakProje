#include "renderer.hpp"

#include "logger.hpp"
#include "manyakSDLimage.hpp"

Renderer* Renderer::sInstance = nullptr;
std::string Renderer::RESOURCE_DIR = "../resources/";

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

SDL_Texture* Renderer::loadTextureFromPath(std::string path, Vec2& size) {
	return sInstance->internalLoadTextureFromPath(path, size);
}

Renderer::Renderer(SDL_Renderer* sdlRenderer) {
	mSdlRenderer = sdlRenderer;
}

void Renderer::internalRender(SDL_Texture* texture, SDL_Rect* pos, SDL_Rect* clip) {
    SDL_SetRenderDrawColor(mSdlRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(mSdlRenderer, pos);
    SDL_SetRenderDrawColor(mSdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderCopy(mSdlRenderer, texture, clip, pos);
}

SDL_Texture* Renderer::internalTextureFromSurface(SDL_Surface* surface) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(mSdlRenderer, surface);
    if (texture == nullptr) {
        Logger::logSdlError("Could not create texture from text surface!");
    }
	return texture;
}

SDL_Texture* Renderer::internalLoadTextureFromPath(std::string path, Vec2& size) {
    SDL_Texture *newTexture = nullptr;
    path = RESOURCE_DIR + path;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        Logger::logSdlImageError("Could not load image!");
        return nullptr;
    }

    size.x = loadedSurface->w;
    size.y = loadedSurface->h;

    newTexture = SDL_CreateTextureFromSurface(mSdlRenderer, loadedSurface);
    if (newTexture == nullptr) {
        Logger::logSdlImageError("Could not create texture from image!");
    }
    SDL_FreeSurface(loadedSurface);
	return newTexture;
}