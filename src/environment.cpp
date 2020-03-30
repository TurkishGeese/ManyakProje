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
#include "action.hpp"
#include "timer.hpp"

#include <filesystem>

#if defined(MANYAK_WIN32)
    std::string resourceDirectory = "../../../../resources/";
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

    mGameState.players[0].attachController();
}

bool Environment::start() {
    if (!mGameState.initialized) return false;

    loadTexture(resourceDirectory + "Idle.png");

    bool running = true;

    SDL_Event e;

    long long lastModified = 0;
    
    Timer fpsTimer;
    while(running) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym ) {
                    Logger::logError(SDL_GetKeyName(e.key.keysym.sym));
                    case SDLK_ESCAPE:
                        Logger::logError("esc");
                        running = false;
                        break;
                    case SDLK_DOWN:
                        Logger::logError("down");
                        mGameState.players[0].input(DOWN);
                        break;
                    case SDLK_UP:
                        Logger::logError("up");
                        mGameState.players[0].input(UP);
                        break;
                    case SDLK_LEFT:
                        Logger::logError("left");
                        mGameState.players[0].input(LEFT);
                        break;
                    case SDLK_RIGHT:
                        Logger::logError("right");
                        mGameState.players[0].input(RIGHT);
                        break;
                }
            }
        }

        float delta = fpsTimer.getElapsedSeconds();
        int deltaInMs = int(delta * 1000.f);
        if (deltaInMs < 16) { // 16.666 ms == 60FPS
            SDL_Delay(16 - deltaInMs);
            delta += fpsTimer.getElapsedSeconds();
        } else {
            Logger::logError("Missed FPS target of 60 this frame.");
        }
        for (int i = 0; i < 4; ++i) {
            if (mGameState.players[i].isPlaying) {
                mGameState.players[i].update(delta);
            }
        }
        
        SDL_RenderClear(mRenderer);
        for (int i = 0; i < 4; ++i) {
            if (mGameState.players[i].isPlaying) {
                mGameState.players[i].render(mRenderer, mTexture);
            }
        }
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