#pragma once

#include <string>

#include "manyakSDL.hpp"
#include "gameState.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Environment  {
public:
    Environment() = default;
    ~Environment();
    
    void initialize();
    bool start();
    void loadTexture(std::string path);

private:
    SDL_Window *mWindow = nullptr;
    SDL_Renderer *mRenderer = nullptr;
    SDL_Surface *mScreenSurface = nullptr;
    SDL_Texture *mTexture = nullptr;

    GameState mGameState;
};