#include <iostream>

#include "manyakSDL.hpp"
#include "manyakSDLimage.hpp"
#include "manyakSDLttf.hpp"

#include "logger.hpp"

void Logger::logError(std::string error) {
    std::string message(error);
    message += "\n";
    SDL_Log("%s", message.c_str());
}

void Logger::logSdlError(std::string error) {
    std::string message(error);
    message += " SDL Error: ";
    message += SDL_GetError();
    message += "\n";
    SDL_Log("%s", message.c_str());
}

void Logger::logSdlImageError(std::string error) {
    std::string message(error);
    message += " SDL_image Error: ";
    message += IMG_GetError();
    message += "\n";
    SDL_Log("%s", message.c_str());
}

void Logger::logSdlTtfError(std::string error) {
    std::string message(error);
    message += " SDL_ttf Error: ";
    message += TTF_GetError();
    message += "\n";
    SDL_Log("%s", message.c_str());
}

