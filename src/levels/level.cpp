#include "level.hpp"

#include "logger.hpp"
#include <string>

Level::~Level() {
	for (GameObject* obj : mGameObjects) {
        delete obj;
    }

    for (UIObject* obj : mUiObjects) {
        delete obj;
    }
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