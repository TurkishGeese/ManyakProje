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
}

void Level::preUpdate() {

}

void Level::update(float delta) {
    preUpdate();

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