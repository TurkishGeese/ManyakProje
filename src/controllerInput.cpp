#include "controllerInput.hpp"

#include "logger.hpp"

InputState ControllerInput::getInputState(SDL_Keycode key) {
	// TODO Move SDL_Keycode s to InputKey
	return NONE;
}

InputState ControllerInput::getInputState(InputKey key) {
	auto iterator = mInputStates.find(key);
	if (iterator == mInputStates.end()) {
		return NONE;
	}

	return iterator->second;
}

void ControllerInput::preUpdateInput() {
	// XXX: I hate that I have to do this. For some reason game controller events are not being received. Instead of trying to receive them,
	// since there is only a handful amount of buttons, we check each button instead. And instead of checking events we literally ask about
	// every single button........ BAH
	for (int button = CONTROLLER_A; button <= CONTROLLER_DPAD_RIGHT; button++) {
		InputKey inputKey = static_cast<InputKey>(button);
		if (SDL_GameControllerGetButton(mSdlController, (SDL_GameControllerButton)getControllerButtonFromInputKey(inputKey)) == 0) {
			if (mInputStates[inputKey] == PRESSED || mInputStates[inputKey] == HELD) {
				mInputStates[inputKey] = RELEASED;
			}
			else {
				mInputStates[inputKey] = NONE;
			}
		}
		else {
			if (mInputStates[inputKey] == PRESSED || mInputStates[inputKey] == HELD) {
				mInputStates[inputKey] = HELD;
			}
			else {
				mInputStates[inputKey] = PRESSED;
			}
		}
	}
}

void ControllerInput::updateInput(SDL_Event& e) {
	(void)e;
	// Note: Look at the comment in the above function
}

ControllerInput::~ControllerInput() {
	if (SDL_GameControllerGetAttached(mSdlController)) {
		SDL_GameControllerClose(mSdlController);
	}
}


void ControllerInput::connectToController(int index) {
	mSdlController = SDL_GameControllerOpen(index);
	if (mSdlController == nullptr) {
		// TODO maybe more graceful error here? Controllers can easily connect/disconnect
		Logger::logSdlError("Could not connect a joystick that should exist.");
		exit(1);
	}
	Logger::logError(std::string("A controller is successfully connected with the name: ") + SDL_GameControllerName(mSdlController));
	mIndex = index;
	mConnected = true;
}

bool ControllerInput::isConnected() {
	// TODO Should this return SDL_JoystickGetAttached(mSdlController)?
	// Is that function cheap/expensive?
	return mConnected;
}

SDL_JoystickID ControllerInput::getControllerId() {
	return mIndex;
}