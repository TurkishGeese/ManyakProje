#include <sys/types.h>
#include <sys/stat.h>

#if defined(MANYAK_WIN32)
    #include <SDL_image.h>
    #define stat _stat
#else
    #include <SDL2_image/SDL_image.h>
    #include <unistd.h>
#endif

#include "environment.hpp"
#include "logger.hpp"

#include <filesystem>

#if defined(MANYAK_WIN32)
    std::string resourceDirectory = "../../../resources/";
#else
    std::string resourceDirectory = "../resources/";
#endif

#ifndef MANYAK_GAME
#define MANYAK_GAME 
    // TODO Get rid of this ifndef when we fix TODO #6
#endif
 
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
    if (mGameState.initialized) return;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Logger::logSdlError("SDL Could not be initialized!");
        return;
    }

    mWindow = SDL_CreateWindow("Manyak Proje", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (mWindow == nullptr) {
        Logger::logSdlError("SDL Could not create a window!");
        return;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (mRenderer == nullptr) {
        Logger::logSdlError("SDL Could not create a renderer!");
        return;
    }
    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        Logger::logSdlImageError("SDL_image could not be initialized!");
        return;
    }

    mGameState.initialized = true;
    mScreenSurface = SDL_GetWindowSurface(mWindow);
}

bool Environment::start() {
    if (!mGameState.initialized) return false;

    Logger::logError("Test5");
    loadTexture(resourceDirectory + "berdem.jpg");
    SDL_Rect renderRect = {0, 0, 320, 240};

    bool running = true;

    SDL_Event e;

    long long lastModified = 0;

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
        SDL_RenderCopy(mRenderer, mTexture, nullptr, &renderRect);
        SDL_RenderPresent(mRenderer);

        struct stat dllResult;
        if (stat(MANYAK_GAME, &dllResult) == 0) {
            if (lastModified == 0) {
                lastModified = dllResult.st_mtime;
            } else if (dllResult.st_mtime != lastModified) {
                return true;
            }
        }
    }

    return false;
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