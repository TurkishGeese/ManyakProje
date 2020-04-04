#include "inputManager.hpp"

InputManager* InputManager::sInstance = nullptr;

void InputManager::initialize() {
    sInstance = new InputManager();
}

void InputManager::quit() {
    delete sInstance;
}


void InputManager::reset() {
    sInstance->internalReset();
}

void InputManager::registerObject(GameObject* obj, InputType inputType) {
    sInstance->internalRegisterObject(obj);
}

void InputManager::updateInput() {
    sInstance->internalUpdateInput();
}

InputState InputManager::getInputState(SDL_Keycode key) {
    return sInstance->getInputState(obj, key);
}

InputState InputManager::getInputState(GameObject* obj, SDL_Keycode key) {
    return sInstance->getInputState(obj, key);
}

InputManager::InputManager() {}

void InputManager::internalReset() {
    mInputMapping.clear();
}

void InputManager::internalRegisterObject(GameObject* obj, InputType inputType) {
    // TODO register object with the correct input
}

void InputManager::internalUpdateInput() {
    // TODO update input states
    //mKeyboard.updateInput();
}

InputState InputManager::internalGetInputState(SDL_Keycode key) {
    //mKeyboard.getInputState(key);
    return NONE;
}

InputState InputManager::internalGetInputState(GameObject* obj, SDL_Keycode key) {
    //return mInputMapping[obj]->getInputState(key);
    return NONE;
}
