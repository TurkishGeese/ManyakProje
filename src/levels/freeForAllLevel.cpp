#include "freeForAllLevel.hpp"

#include "player.hpp"
#include "uiText.hpp"
#include "inputManager.hpp"

FreeForAllLevel::FreeForAllLevel() {
	mGameObjects = std::vector<GameObject*>(1);
	mUiObjects = std::vector<UIObject*>(1);
    mGameObjects[0] = new Player();
    mUiObjects [0] = new UIText("Bora", 0, 0, {255, 0, 0});

	InputManager::registerObject(mGameObjects[0], KEYBOARD);
}