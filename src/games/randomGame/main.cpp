#include <filesystem>

#include "gameMain.hpp"
#include "manyakSDL.hpp"

#include "logger.hpp"

#include "renderer.hpp"
#include "assetManager.hpp"

#if defined(MANYAK_WIN32)
#include <Windows.h>

int wmain(int argc, const char* argv[]) {
#else
int main(int argc, const char* argv[]) {
#endif
    // TODO make this resource setting part better
    AssetManager::RESOURCE_DIR = GAME_RESOURCE_DIR;
    Renderer::RESOURCE_DIR = GAME_RESOURCE_DIR;
    Environment* environment = getEnvironment();
    startGame(environment);
}