#include "keyboardInput.hpp"

InputState KeyboardInput::getInputState(SDL_Keycode key) {
	auto iterator = mInputStates.find(key);
	if (iterator == mInputStates.end()) {
		return NONE;
	}

	return iterator->second;
}

void KeyboardInput::updateInput() {
	// If the key was pressed earlier, now it's being held.
	// If the key was released earlier, now it has no state.
	for (const auto& it : mInputStates)
	{
		if (it.second == PRESSED) {
			mInputStates[it.first] = HELD;
		}
		else if (it.second == RELEASED) {
			// XXX: I'm not sure what's the best way of handling this here. If we remove an item the map internal functions `might` be slow.
			// So we wouldn't want to do this. However, the other option is to update the key's value to a NONE. But in that case it'll always stay
			// inside the mapping. At each frame we loop all values inside the map. Now we have an extra key to check every frame. My guy tells me
			// that erasing should be better. However, we should really evaluate this. Perhaps there is no difference. I think this points to me
			// not storing my data correctly. So ideally we should store these states differently.
			mInputStates.erase(it.first);
		}
	}

	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			// TODO there has to be a nicer way of exiting the game
			exit(0);
		}
		else if (e.type == SDL_KEYDOWN) {
			mInputStates[e.key.keysym.sym] = PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			mInputStates[e.key.keysym.sym] = RELEASED;
		}
		// TODO on keyup and keydown, we will probably need modifiers (e.key.keysym.mod) such as ctrl and alt.
		// Should find a way to record these as well.
		// TODO mouse movements
	}
}

KeyboardInput::~KeyboardInput() {}