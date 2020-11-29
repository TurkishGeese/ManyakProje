#include <filesystem>

#include "gameMain.hpp"
#include "manyakSDL.hpp"

#include "logger.hpp"

#include "renderer.hpp"
#include "assetManager.hpp"
#include "master.hpp"
#include "textureComponent.hpp"
#include "transformComponent.hpp"
#include "physics2DComponent.hpp"
#include "inputComponent.hpp"
#include "uiInputComponent.hpp"
#include "renderSystem.hpp"
#include "inputSystem.hpp"
#include "uiInputSystem.hpp"
#include "physicsSystem2D.hpp"

#if defined(MANYAK_WIN32)
#include <Windows.h>

int wmain(int argc, const char* argv[]) {
#else
int main(int argc, const char* argv[]) {
#endif
    Master* master = Master::getInstance();

    // TODO this should be data driven once we have a data layer
    master->registerComponentType<TextureComponent>();
    master->registerComponentType<TransformComponent>();
    master->registerComponentType<Physics2DComponent>();
    master->registerComponentType<InputComponent>();
    master->registerComponentType<UIInputComponent>();

    master->registerSystem<RenderSystem>();
    master->registerSystem<InputSystem>();
    master->registerSystem<UIInputSystem>();
    PhysicsSystem2D* physicsSystem = master->registerSystem<PhysicsSystem2D>();

    physicsSystem->setWindowSize({ 640.f, 480.f });
    physicsSystem->setWorldSize({ 50.0f, 100.0f });

    // TODO make this resource setting part better
    AssetManager::RESOURCE_DIR = GAME_RESOURCE_DIR;
    Renderer::RESOURCE_DIR = GAME_RESOURCE_DIR;
    Environment* environment = getEnvironment();
    startGame(environment);
}