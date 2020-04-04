#include "level.hpp"

#include <string>

#include "inputManager.hpp"

Level::~Level() {
	for (GameObject* obj : mGameObjects) {
        delete obj;
    }

    for (UIObject* obj : mUiObjects) {
        delete obj;
    }
    InputManager::reset();
}

void Level::update(float delta) {
    for (GameObject* obj : mGameObjects) {
        obj->update(delta);
    }
}

void Level::render() {
	for (GameObject* obj : mGameObjects) {
        obj->render();
    }

    for (UIObject* obj : mUiObjects) {
        obj->render();
    }
}