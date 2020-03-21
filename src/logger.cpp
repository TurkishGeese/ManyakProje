#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "logger.hpp"

void Logger::logError(const char *error) {
    getSingleton().internalLogError(error);
}

void Logger::logSdlError(const char *error) {
    getSingleton().internalLogSdlError(error);
}

void Logger::logSdlImageError(const char *error) {
    getSingleton().internalLogSdlImageError(error);
}

Logger& Logger::getSingleton() {
    static Logger logger;
    return logger;
}

void Logger::internalLogError(const char *error) {
    std::cout << error << "\n";
}

void Logger::internalLogSdlError(const char *error) {
    std::cout << error << " SDL_Error: " << SDL_GetError() << "\n";
}

void Logger::internalLogSdlImageError(const char *error) {
    std::cout << error << " SDL_Error: " << IMG_GetError() << "\n";
}
