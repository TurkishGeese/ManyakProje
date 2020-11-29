#include "freeForAllLevel.hpp"

#include "playerConfiguration.hpp"
#include "playerKeyboardConfiguration.hpp"
#include "playerAi.hpp"

#include "master.hpp"
#include "transformComponent.hpp"
#include "physics2DComponent.hpp"
#include "physicsSystem2D.hpp"

FreeForAllLevel::FreeForAllLevel() {
	// TODO Something is funky about these sizes
	Game::createWall({ -1.0f, 50.f }, { 1.0f, 50.f});
	Game::createWall({ 51.0f, 50.f }, { 1.0f, 50.f });
	Game::createWall({ 25.0f, 101.f }, { 50.f, 1.f});
	Game::createWall({ 25.0f, -1.f }, { 50.f, 1.f});

	mConfigurations = std::vector<InputConfiguration*>(5);
	mConfigurations[0] = new PlayerKeyboardConfiguration();
	mConfigurations[1] = new PlayerAi();
	mConfigurations[2] = new PlayerAi();
	mConfigurations[3] = new PlayerAi();
	mConfigurations[4] = new PlayerAi();

	UI::createText("Bora", { 0, 0 }, { 255, 0, 0 });
	Game::createPlayer(InputType::KEYBOARD, mConfigurations[0]);
	Game::createPlayer(InputType::AI_PLAYER, mConfigurations[1]);
	Game::createPlayer(InputType::AI_PLAYER, mConfigurations[2]);
	Game::createPlayer(InputType::AI_PLAYER, mConfigurations[3]);
	Game::createPlayer(InputType::AI_PLAYER, mConfigurations[4]);

}