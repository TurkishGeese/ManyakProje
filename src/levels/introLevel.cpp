#include "introLevel.hpp"

#include "environment.hpp"
#include "freeForAllLevel.hpp"
#include "inputManager.hpp"
#include "manyakSDL.hpp"
#include "uiText.hpp"
#include "uiButton.hpp"

IntroLevel::IntroLevel() {
    mUiObjects = std::vector<UIObject*>(2);
    mGameObjects = std::vector<GameObject*>(0);
    mUiObjects[0] = new UIText("Intro Level", 0, 0, { 255, 0, 0 });
    mUiObjects[1] = new UIButton("buttonIdle.png", "buttonactive.png", 100.0f, 100.0f, 300.0f, 100.0f);
}

void IntroLevel::preUpdate() {
    if (InputManager::getActionState(Action::SELECT) == InputState::PRESSED) {
        InputManager::reset();
        Environment::sChangeLevel = new FreeForAllLevel();
    }
}