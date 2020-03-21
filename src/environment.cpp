#include <SDL2_image/SDL_image.h>

#include "environment.hpp"
#include "logger.hpp"

#include <filesystem>
 
Environment::~Environment() {
    if (mWindow != nullptr)
        SDL_DestroyWindow(mWindow);

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

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        Logger::logSdlImageError("SDL_image could not be initialized!");
        mIsWorking = false;
        return;
    }

    mScreenSurface = SDL_GetWindowSurface(mWindow);

    Logger::logError(std::filesystem::current_path().string().c_str());
}

void Environment::start() {
    if (!mIsWorking) return;

    SDL_FillRect(mScreenSurface, NULL, SDL_MapRGB(mScreenSurface->format, 0xFF, 0xFF, 0xFF));
    loadMedia("../resources/Gunes.jpg");

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
        SDL_BlitSurface(mMedia, nullptr, mScreenSurface, nullptr);
        SDL_UpdateWindowSurface(mWindow);
    }

    SDL_Delay(2000);
}

void Environment::loadMedia(std::string path) {
    SDL_Surface *optimizedSurface = nullptr;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        Logger::logSdlImageError("Could not load image!");
        return;
    }
    optimizedSurface = SDL_ConvertSurface(loadedSurface, mScreenSurface->format, 0);
    if (optimizedSurface == nullptr) {
        Logger::logSdlImageError("Could not optimized image!");
    } else {
        mMedia = optimizedSurface;
    }
    SDL_FreeSurface(loadedSurface);
}