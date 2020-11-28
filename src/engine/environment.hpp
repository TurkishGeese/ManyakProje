#pragma once

#include <string>

#include "manyakSDL.hpp"
#include "manyakSDLttf.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Level;

class Environment  {
public:
    Environment() = default;
    ~Environment();
    
    void initialize();
    bool start();

    static TTF_Font* sFont;
    static Level* sChangeLevel;
private:
    SDL_Window *mWindow = nullptr;
    SDL_Renderer *mRenderer = nullptr;
    SDL_Surface *mScreenSurface = nullptr;
};