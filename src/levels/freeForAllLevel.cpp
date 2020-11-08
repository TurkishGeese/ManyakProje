#include "freeForAllLevel.hpp"

#include "player.hpp"
#include "uiText.hpp"
#include "inputManager.hpp"
#include "playerConfiguration.hpp"
#include "playerKeyboardConfiguration.hpp"
#include "playerAi.hpp"

#include "master.hpp"
#include "transformComponent.hpp"
#include "physics2DComponent.hpp"
#include "physicsSystem2D.hpp"

void defineWall(Vec2 pos, Vec2 size)
{
	Master* master = Master::getInstance();
	Entity entity = master->createEntity();
	master->addComponentOfType<TransformComponent>(entity);
	Physics2DComponent* physics2DComponent = master->addComponentOfType<Physics2DComponent>(entity);
	PhysicsSystem2D* physicsSystem = master->getSystem<PhysicsSystem2D>();
	physicsSystem->initializeEntityAsStaticBody(entity, pos, size);
	master->finalizeEntity(entity);
}

FreeForAllLevel::FreeForAllLevel() {
	// TODO Something is funky about these sizes
	defineWall({ -1.0f, 50.f }, { 1.0f, 50.f});
	defineWall({ 51.0f, 50.f }, { 1.0f, 50.f });
	defineWall({ 25.0f, 101.f }, { 50.f, 1.f});
	defineWall({ 25.0f, -1.f }, { 50.f, 1.f});

	mGameObjects = std::vector<GameObject*>(2);
	mConfigurations = std::vector<InputConfiguration*>(2);
	mUiObjects = std::vector<UIObject*>(1);
    mGameObjects[0] = new Player();
	mConfigurations[0] = new PlayerKeyboardConfiguration();
    //mGameObjects[1] = new Player();
	//mConfigurations[1] = new PlayerConfiguration();
	Player* ai = new Player();
    mGameObjects[1] = ai;
	mConfigurations[1] = new PlayerAi(ai);
    mUiObjects [0] = new UIText("Bora", {0, 0}, {255, 0, 0});

	InputManager::registerObject(mGameObjects[0], InputType::KEYBOARD, mConfigurations[0]);
	//InputManager::registerObject(mGameObjects[1], InputType::CONTROLLER, mConfigurations[1]);
	InputManager::registerObject(mGameObjects[1], InputType::AI_PLAYER, mConfigurations[1]);
}