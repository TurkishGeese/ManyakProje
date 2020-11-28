#include "level.hpp"

#include <string>

#include "inputManager.hpp"

Level::~Level() {

    for (InputConfiguration* config : mConfigurations) {
        delete config;
    }
}

void Level::preUpdate() {

}

void Level::update(float delta) {
    (void)delta;
    preUpdate();
}

void Level::render() {
}