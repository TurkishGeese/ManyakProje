#include <iostream>

#if defined(MANYAK_MAC)
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
#elif defined(MANYAK_WIN32)
    #include <SDL.h>
    #include <SDL_image.h>
#endif

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
    std::string message(error);
    message += "\n";
    SDL_Log(message.c_str());
}

void Logger::internalLogSdlError(const char *error) {
    std::string message(error);
    message += " SDL_Error: ";
    message += SDL_GetError();
    message += "\n";
    SDL_Log(message.c_str());
}

void Logger::internalLogSdlImageError(const char *error) {
    std::string message(error);
    message += " SDL_Error: ";
    message += IMG_GetError();
    message += "\n";
    SDL_Log(message.c_str());
}

