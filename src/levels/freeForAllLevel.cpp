#include "freeForAllLevel.hpp"

#include "player.hpp"
#include "uiText.hpp"
#include "inputManager.hpp"
#include "playerConfiguration.hpp"
#include "playerKeyboardConfiguration.hpp"
#include "playerAi.hpp"

FreeForAllLevel::FreeForAllLevel() {
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