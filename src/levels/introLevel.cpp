#include "introLevel.hpp"

#include "environment.hpp"
#include "freeForAllLevel.hpp"
#include "inputManager.hpp"
#include "manyakSDL.hpp"
#include "uiText.hpp"

IntroLevel::IntroLevel() {
    mUiObjects = std::vector<UIObject*>(1);
    mGameObjects = std::vector<GameObject*>(0);
    mUiObjects[0] = new UIText("Intro Level", 0, 0, { 255, 0, 0 });
}

void IntroLevel::preUpdate() {
    if (InputManager::getActionState(Action::SELECT) == InputState::PRESSED) {
        InputManager::reset();
        Environment::sChangeLevel = new FreeForAllLevel();
    }
}