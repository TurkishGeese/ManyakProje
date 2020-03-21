#pragma once

#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Environment  {
public:
    Environment() = default;
    ~Environment();
    
    void initialize();
    void start();
    void loadMedia(std::string path);

private:
    SDL_Window *mWindow = nullptr;
    SDL_Surface *mScreenSurface = nullptr;
    SDL_Surface *mMedia = nullptr;
    bool mIsWorking = true;
};