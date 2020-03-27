#include <iostream>

#if defined(MANYAK_WIN32)
    #include <SDL.h>
    #include <SDL_image.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
#endif

#include "logger.hpp"

void Logger::logError(std::string error) {
    std::string message(error);
    message += "\n";
    SDL_Log("%s", message.c_str());
}

void Logger::logSdlError(std::string error) {
    std::string message(error);
    message += " SDL_Error: ";
    message += SDL_GetError();
    message += "\n";
    SDL_Log("%s", message.c_str());
}

void Logger::logSdlImageError(std::string error) {
    std::string message(error);
    message += " SDL_Error: ";
    message += IMG_GetError();
    message += "\n";
    SDL_Log("%s", message.c_str());
}

