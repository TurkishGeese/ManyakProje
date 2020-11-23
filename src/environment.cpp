#include <sys/types.h>
#include <sys/stat.h>

#if defined(MANYAK_WIN32)
    #define stat _stat
#else
    #include <unistd.h>
#endif

#include "environment.hpp"

#include "manyakSDLimage.hpp"

#include "renderer.hpp"
#include "inputManager.hpp"
#include "logger.hpp"
#include "timer.hpp"
#include "level.hpp"
#include "introLevel.hpp"
#include "assetManager.hpp"
#include "master.hpp"
#include "textureComponent.hpp"
#include "transformComponent.hpp"
#include "renderSystem.hpp"
#include "physics2DComponent.hpp"
#include "physicsSystem2D.hpp"
#include "inputComponent.hpp"
#include "inputSystem.hpp"
#include "uiInputComponent.hpp"
#include "uiInputSystem.hpp"

#ifndef MANYAK_GAME
#define MANYAK_GAME 
    // TODO Get rid of this ifndef when we fix TODO #6
#endif

TTF_Font* Environment::sFont = nullptr;
Level* Environment::sChangeLevel = nullptr;
 
Environment::~Environment() {
    InputManager::quit();
    Renderer::quit();

    if (mRenderer != nullptr)
        SDL_DestroyRenderer(mRenderer);

    if (mWindow != nullptr)
        SDL_DestroyWindow(mWindow);

    if (sFont != nullptr)
        TTF_CloseFont(sFont);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Environment::initialize() {

    if (TTF_Init() == -1) {
        Logger::logSdlTtfError("SDL_ttf could not be initialized!");
        return;
    }

    sFont = TTF_OpenFont((Renderer::RESOURCE_DIR + "KenneyBold.ttf").c_str(), 28);
    if (sFont == nullptr) {
        Logger::logSdlTtfError("Could not initialize the font!");
        return;
    }

    // TODO: Investigate why TTF always needs to be reinitialized as a library and fails to load font otherwise.
    // Currently, we only try to load a texture at the beginning. Will we have the same problem with SDL_image
    // if we tried to load more stuff later? This is not exactly true since we can dynamically change the picture.
    // Weird. If TTF state is somehow disappearing, all sorts of other stuff can happen with other SDL libraries.
    if (mGameState.initialized) return;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
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

    mScreenSurface = SDL_GetWindowSurface(mWindow);

    mGameState.initialized = true;
}

bool Environment::start() {
    Renderer::initialize(mRenderer);
    InputManager::initialize();
    AssetManager::initialize();
    if (!mGameState.initialized) return false;

    Master* master = Master::getInstance();
    // TODO create an active game system that allows the "game" to register what it wants
    master->registerComponentType<TextureComponent>();
    master->registerComponentType<TransformComponent>();
    master->registerComponentType<Physics2DComponent>();
    master->registerComponentType<InputComponent>();
    master->registerComponentType<UIInputComponent>();
    PhysicsSystem2D* physicsSystem = master->registerSystem<PhysicsSystem2D>();
    master->registerSystem<RenderSystem>();
    master->registerSystem<InputSystem>();
    master->registerSystem<UIInputSystem>();

    physicsSystem->setWindowSize({640.f, 480.f});
    physicsSystem->setWorldSize({50.0f, 100.0f});

    bool running = true;

    Level* level = new IntroLevel();

    long long lastModified = 0;
    
    Timer fpsTimer;
    while(running) {
        InputManager::updateInput();

        float delta = fpsTimer.getElapsedSeconds();
        int deltaInMs = int(delta * 1000.f);
        if (deltaInMs < 16) { // 16.666 ms == 60FPS
            SDL_Delay(16 - deltaInMs);
            delta += fpsTimer.getElapsedSeconds();
        } else {
            Logger::logError("Missed FPS target of 60 this frame.");
        }

        level->update(delta);

        if (sChangeLevel != nullptr) {
            delete level;
            level = sChangeLevel;
            sChangeLevel = nullptr;
        }

        SDL_RenderClear(mRenderer);
        level->render();
        master->update(delta);

        SDL_RenderPresent(mRenderer);

        struct stat dllResult;
        if (stat(MANYAK_GAME, &dllResult) == 0) {
            if (lastModified == 0) {
                lastModified = dllResult.st_mtime;
            } else if (dllResult.st_mtime != lastModified) {
                delete level;
                return true;
            }
        }
    }

    delete master;
    delete level;
    return false;
}
