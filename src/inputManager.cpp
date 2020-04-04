#include "inputManager.hpp"

#include "logger.hpp"

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
    sInstance->internalRegisterObject(obj, inputType);
}

void InputManager::updateInput() {
    sInstance->internalUpdateInput();
}

InputState InputManager::getInputState(SDL_Keycode key) {
    return sInstance->internalGetInputState(key);
}

InputState InputManager::getInputState(GameObject* obj, SDL_Keycode key) {
    return sInstance->internalGetInputState(obj, key);
}

InputManager::InputManager() {}

void InputManager::internalReset() {
    mInputMapping.clear();
}

void InputManager::internalRegisterObject(GameObject* obj, InputType inputType) {
    if (inputType == KEYBOARD) {
        mInputMapping[obj] = &mKeyboard;
    }
    else if (inputType == AI_PLAYER) {
        mInputMapping[obj] = &mAiInput;
    }
    else if (inputType == CONTROLLER) {
        // TODO controllers. Should grab a new controller here?
        mInputMapping[obj] = nullptr;
    }
    else {
        // TODO assert
        Logger::logError("Invalid input type given to register object.");
        exit(1);
    }
}

void InputManager::internalUpdateInput() {
    mKeyboard.updateInput();
    mAiInput.updateInput();
}

InputState InputManager::internalGetInputState(SDL_Keycode key) {
    return mKeyboard.getInputState(key);
}

InputState InputManager::internalGetInputState(GameObject* obj, SDL_Keycode key) {
    return mInputMapping[obj]->getInputState(key);
}
