#include "aiInput.hpp"

InputState AIInput::getInputState(InputKey key) {
	// TODO is it okay for AI to only have 2 modes? Either none for no action
	// or HELD if there is an action. The specific ai configuration only ever
	// returns a valid input key if it should be pressed or held.
	if (key == InputKey::INVALID) {
		return InputState::NONE;
	}
	return InputState::HELD;
}

void AIInput::updateInput(SDL_Event& e) {
	(void)e; // AIInput does nothing with events
}

AIInput::~AIInput() {}