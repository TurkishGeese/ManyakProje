#include "introLevel.hpp"

#include "environment.hpp"
#include "freeForAllLevel.hpp"
#include "inputManager.hpp"
#include "assetManager.hpp"
#include "manyakSDL.hpp"
#include "uiObject.hpp"
#include "master.hpp"

void changeLevelToFreeForAll()
{
    Environment::sChangeLevel = new FreeForAllLevel();
}

void startFunc(){
    AssetManager::reset();

    Master::getInstance()->reset(changeLevelToFreeForAll);
}

IntroLevel::IntroLevel() {
    UI::createText("Intro Level", { 0, 0 }, { 0, 0, 0 });
    UI::createButton(startFunc, "start", { 100.0f, 100.0f }, { 300.0f, 100.0f });
}

void IntroLevel::preUpdate() {
}
