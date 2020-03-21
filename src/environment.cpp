#include <SDL2_image/SDL_image.h>

#include "environment.hpp"
#include "logger.hpp"

#include <filesystem>
 
Environment::~Environment() {
    if (mTexture != nullptr)
        SDL_DestroyTexture(mTexture);

    if (mRenderer != nullptr)
        SDL_DestroyRenderer(mRenderer);

    if (mWindow != nullptr)
        SDL_DestroyWindow(mWindow);

    IMG_Quit();
    SDL_Quit();
}

void Environment::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Logger::logSdlError("SDL Could not be initialized!");
        mIsWorking = false;
        return;
    }

    mWindow = SDL_CreateWindow("Manyak Proje", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (mWindow == nullptr) {
        Logger::logSdlError("SDL Could not create a window!");
        mIsWorking = false;
        return;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (mRenderer == nullptr) {
        Logger::logSdlError("SDL Could not create a renderer!");
        mIsWorking = false;
        return;
    }
    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        Logger::logSdlImageError("SDL_image could not be initialized!");
        mIsWorking = false;
        return;
    }

    mScreenSurface = SDL_GetWindowSurface(mWindow);
}

void Environment::start() {
    if (!mIsWorking) return;

    loadTexture("../resources/Gunes.jpg");

    bool running = true;

    SDL_Event e;

    while(running) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym ) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                }
            }
        }
        
        SDL_RenderClear(mRenderer);
        SDL_RenderCopy(mRenderer, mTexture, nullptr, nullptr);
        SDL_RenderPresent(mRenderer);
    }

    SDL_Delay(2000);
}

void Environment::loadTexture(std::string path) {
    SDL_Texture *newTexture = nullptr;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        Logger::logSdlImageError("Could not load image!");
        return;
    }
    newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
    if (newTexture == nullptr) {
        Logger::logSdlImageError("Could not create texture from image!");
    } else {
        mTexture = newTexture;
    }
    SDL_FreeSurface(loadedSurface);
}