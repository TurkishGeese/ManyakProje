#include <filesystem>

#include "gameState.hpp"
#include "gameMain.hpp"
#include "manyakSDL.hpp"

#include "logger.hpp"

startGameFunction startGameFunc = nullptr;
getEnvironmentFunction getEnvironmentFunc = nullptr;

void unloadGameDll(bool reload = false) {
    static void* gameDllHandle = nullptr;
    if (gameDllHandle != nullptr) {
        SDL_UnloadObject(gameDllHandle);
    }

    if (reload) {
        try {
            std::filesystem::copy_file(MANYAK_GAME, "./temp_manyakGame.dll", std::filesystem::copy_options::overwrite_existing);
        }
        catch (std::filesystem::filesystem_error & e) {
            Logger::logError("Filesystem error: " + ((std::error_code)e.code).message());
        }
        gameDllHandle = SDL_LoadObject("./temp_manyakGame.dll");
        if (gameDllHandle == nullptr) {
            Logger::logSdlError("Could not load the game dll.");
            exit(1);
        }
        
        startGameFunc = (startGameFunction)SDL_LoadFunction(gameDllHandle, "startGame");
        if (startGameFunc == nullptr) {
            Logger::logSdlError("Could not load the start game function.");
            exit(1);
        }

        getEnvironmentFunc = (getEnvironmentFunction)SDL_LoadFunction(gameDllHandle, "getEnvironment");
        if (getEnvironmentFunc == nullptr) {
            Logger::logSdlError("Could not load the get environment function.");
            exit(1);
        }
    }
}

#if defined(MANYAK_MAC)
int main(int argc, const char* argv[]) {
#elif defined(MANYAK_WIN32)
#include <Windows.h>

int wmain(int argc, const char* argv[]) {
#endif
    unloadGameDll(true);
    Environment* environment = getEnvironmentFunc();
    while (startGameFunc(environment)) {
        unloadGameDll(true);
        Logger::logError("Successfully reloaded.");
    }
    unloadGameDll();
}