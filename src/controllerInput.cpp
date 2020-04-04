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
	// If the key was pressed earlier, now it's being held.
	// If the key was released earlier, now it has no state.
	for (std::map<InputKey, InputState>::iterator it = mInputStates.begin(); it != mInputStates.end();)
	{
		// Need to get next now because we might delete the current iterator
		auto curIt = it;
		it++;

		if (curIt->second == PRESSED) {
			mInputStates[curIt->first] = HELD;
		}
		else if (curIt->second == RELEASED) {
			// XXX: Look at KeyboardInput
			mInputStates.erase(curIt->first);
		}
	}
}

void ControllerInput::updateInput(SDL_Event& e) {
	if (e.type == SDL_CONTROLLERAXISMOTION) {
		// TODO Controller axis motion
	}
	else if (e.type == SDL_CONTROLLERBUTTONDOWN) {
		mInputStates[getInputKeyFromControllerButton(e.cbutton.button)] = PRESSED;
	}
	else if (e.type == SDL_CONTROLLERBUTTONUP) {
		mInputStates[getInputKeyFromControllerButton(e.cbutton.button)] = RELEASED;
	}
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