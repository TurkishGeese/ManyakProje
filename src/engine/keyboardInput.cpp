#include "keyboardInput.hpp"

InputState KeyboardInput::getInputState(InputKey key) {
	auto iterator = mInputStates.find(key);
	if (iterator == mInputStates.end()) {
		return InputState::NONE;
	}

	return iterator->second;
}

void KeyboardInput::preUpdateInput() {
	// If the key was pressed earlier, now it's being held.
	// If the key was released earlier, now it has no state.
	for (std::map<InputKey, InputState>::iterator it = mInputStates.begin(); it != mInputStates.end();)
	{
		// Need to get next now because we might delete the current iterator
		auto curIt = it;
		it++;

		if (curIt->second == InputState::PRESSED) {
			mInputStates[curIt->first] = InputState::HELD;
		}
		else if (curIt->second == InputState::RELEASED) {
			// XXX: I'm not sure what's the best way of handling this here. If we remove an item the map internal functions `might` be slow.
			// So we wouldn't want to do this. However, the other option is to update the key's value to a NONE. But in that case it'll always stay
			// inside the mapping. At each frame we loop all values inside the map. Now we have an extra key to check every frame. My guy tells me
			// that erasing should be better. However, we should really evaluate this. Perhaps there is no difference. I think this points to me
			// not storing my data correctly. So ideally we should store these states differently.
			mInputStates.erase(curIt->first);
		}
	}

	int x, y;
	SDL_GetMouseState(&x, &y);
	mMouseLoc = { (float)x, (float)y };

	mModState = SDL_GetModState();
}

void KeyboardInput::updateInput(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN) {
		mInputStates[getInputKeyFromSdlKey(e.key.keysym.sym)] = InputState::PRESSED;
	}
	else if (e.type == SDL_KEYUP) {
		mInputStates[getInputKeyFromSdlKey(e.key.keysym.sym)] = InputState::RELEASED;
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN) {
		mInputStates[getInputKeyFromMouseButton(e.button)] = InputState::PRESSED;
	}
	else if (e.type == SDL_MOUSEBUTTONUP) {
		mInputStates[getInputKeyFromMouseButton(e.button)] = InputState::RELEASED;
	}
}

Vec2 KeyboardInput::getMouseLocation() {
	return mMouseLoc;
}

bool KeyboardInput::ctrlDown() {
	return mModState & KMOD_CTRL;
}

bool KeyboardInput::altDown() {
	return mModState & KMOD_ALT;
}

bool KeyboardInput::shiftDown() {
	return mModState & KMOD_SHIFT;
}

KeyboardInput::~KeyboardInput() {}