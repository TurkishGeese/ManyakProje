#include "introLevel.hpp"

#include "environment.hpp"
#include "freeForAllLevel.hpp"
#include "inputManager.hpp"
#include "assetManager.hpp"
#include "manyakSDL.hpp"
#include "uiText.hpp"
#include "uiButton.hpp"
#include "uiObject.hpp"
#include "master.hpp"

//We defined this function in IntroLevel as a method but then got an error related to function passing
void startFunc(){
    InputManager::reset();
    AssetManager::reset();
    Master::getInstance()->removeAllEntities();

    Environment::sChangeLevel = new FreeForAllLevel();
}

IntroLevel::IntroLevel() {
    mUiObjects = std::vector<UIObject*>(0);
    mGameObjects = std::vector<GameObject*>(0);
    //mUiObjects[0] = new UIText("Intro Level", {0, 0}, { 0, 0, 0 });
    //mUiObjects[1] = new UIButton(startFunc, "start", {100.0f, 100.0f}, {300.0f, 100.0f});
    UI::createText("Intro Level", { 0, 0 }, { 0, 0, 0 });
    UI::createButton(startFunc, "start", { 100.0f, 100.0f }, { 300.0f, 100.0f });
}

void IntroLevel::preUpdate() {
    startFunc();
    if (InputManager::getActionState(Action::SELECT) == InputState::PRESSED) {
        startFunc();
    }
}
