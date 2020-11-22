#include "introLevel.hpp"

#include "environment.hpp"
#include "freeForAllLevel.hpp"
#include "inputManager.hpp"
#include "assetManager.hpp"
#include "manyakSDL.hpp"
#include "uiObject.hpp"
#include "master.hpp"

//We defined this function in IntroLevel as a method but then got an error related to function passing
void startFunc(){
    AssetManager::reset();
    Master::getInstance()->removeAllEntities();

    Environment::sChangeLevel = new FreeForAllLevel();
}

IntroLevel::IntroLevel() {
    UI::createText("Intro Level", { 0, 0 }, { 0, 0, 0 });
    UI::createButton(startFunc, "start", { 100.0f, 100.0f }, { 300.0f, 100.0f });
}

void IntroLevel::preUpdate() {
    startFunc();
    if (InputManager::getActionState(Action::SELECT) == InputState::PRESSED) {
        startFunc();
    }
}
