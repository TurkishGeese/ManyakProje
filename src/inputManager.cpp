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

InputState InputManager::getInputState(InputKey key) {
    return sInstance->internalGetInputState(key);
}

InputState InputManager::getInputState(GameObject* obj, InputKey key) {
    return sInstance->internalGetInputState(obj, key);
}

Vec2 InputManager::getMouseLocation() {
    return sInstance->internalGetMouseLocation();
}

bool InputManager::ctrlDown() {
    return sInstance->internalCtrlDown();
}

bool InputManager::altDown() {
    return sInstance->internalAltDown();
}

bool InputManager::shiftDown() {
    return sInstance->internalShiftDown();
}

InputManager::InputManager() {
    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        if (SDL_IsGameController(i)) {
            if (!mController1.isConnected()) {
                mController1.connectToController(i);
            }
            else if (!mController2.isConnected()) {
                mController2.connectToController(i);
            }
            else if (!mController3.isConnected()) {
                mController3.connectToController(i);
            }
            else if (!mController4.isConnected()) {
                mController4.connectToController(i);
            }
            else {
                Logger::logError("More than 4 controllers are connected!");
            }
        }
    }

}

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
        if (!mController1Used) {
            mController1Used = true;
            mInputMapping[obj] = &mController1;
        }
        else if (!mController2Used) {
            mController2Used = true;
            mInputMapping[obj] = &mController2;
        }
        else if (!mController3Used) {
            mController3Used = true;
            mInputMapping[obj] = &mController3;
        }
        else if (!mController4Used) {
            mController4Used = true;
            mInputMapping[obj] = &mController4;
        }
        else {
            Logger::logError("Tried to register more than 4 objects to controllers.");
            exit(1);
        }
    }
    else {
        // TODO assert
        Logger::logError("Invalid input type given to register object.");
        exit(1);
    }
}

void InputManager::internalUpdateInput() {
    mKeyboard.preUpdateInput();
    mController1.preUpdateInput();
    mController2.preUpdateInput();
    mController3.preUpdateInput();
    mController4.preUpdateInput();

    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            // TODO there has to be a nicer way of exiting the game
            exit(0);
        }

        if (e.type == SDL_KEYDOWN ||
            e.type == SDL_KEYUP ||
            e.type == SDL_MOUSEBUTTONDOWN ||
            e.type == SDL_MOUSEBUTTONUP) {
            mKeyboard.updateInput(e);
        }
        else if (e.type == SDL_CONTROLLERAXISMOTION ||
            e.type == SDL_CONTROLLERBUTTONDOWN ||
            e.type == SDL_CONTROLLERBUTTONUP) {
            // Note: Look at ControllerInput.cpp::preUpdate() for more info.
            Logger::logError("Should not have received a controller input event.");
        }
        else if (e.type == SDL_CONTROLLERDEVICEADDED ||
            e.type == SDL_CONTROLLERDEVICEREMOVED) {
            // TODO Handle controller connect/disconnect
        }
    }

    mAiInput.updateInput(e); // e is ignored
}

InputState InputManager::internalGetInputState(SDL_Keycode key) {
    return mKeyboard.getInputState(key);
}

InputState InputManager::internalGetInputState(GameObject* obj, SDL_Keycode key) {
    return mInputMapping[obj]->getInputState(key);
}

InputState InputManager::internalGetInputState(InputKey key) {
    return mKeyboard.getInputState(key);
}

InputState InputManager::internalGetInputState(GameObject* obj, InputKey key) {
    return mInputMapping[obj]->getInputState(key);
}

Vec2 InputManager::internalGetMouseLocation() {
    return mKeyboard.getMouseLocation();
}

bool InputManager::internalCtrlDown() {
    return mKeyboard.ctrlDown();
}

bool InputManager::internalAltDown() {
    return mKeyboard.altDown();
}

bool InputManager::internalShiftDown() {
    return mKeyboard.shiftDown();
}