#include "inputManager.hpp"

#include "logger.hpp"
#include "playerConfiguration.hpp"

#include <assert.h>

InputManager* InputManager::sInstance = nullptr;

void InputManager::initialize() {
    sInstance = new InputManager();
}

void InputManager::quit() {
    delete sInstance;
}

Input* InputManager::registerObject(InputType inputType) {
    return sInstance->internalRegisterObject(inputType);
}

void InputManager::updateInput() {
    sInstance->internalUpdateInput();
}

InputState InputManager::getActionState(Action action) {
    return sInstance->internalGetActionState(action);
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
        if (!SDL_IsGameController(i)) continue;

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

Input* InputManager::internalRegisterObject(InputType inputType) {
    if (inputType == InputType::KEYBOARD) {
        return &mKeyboard;
    }
    else if (inputType == InputType::AI_PLAYER) {
        return &mAiInput;
    }
    else if (inputType == InputType::CONTROLLER) {
        if (!mController1Used) {
            mController1Used = true;
            return &mController1;
        }
        else if (!mController2Used) {
            mController2Used = true;
            return &mController2;
        }
        else if (!mController3Used) {
            mController3Used = true;
            return &mController3;
        }
        else if (!mController4Used) {
            mController4Used = true;
            return &mController4;
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

InputState InputManager::internalGetActionState(Action action) {
    return mKeyboard.getInputState(mDefaultConfig.getInputKey(action));
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