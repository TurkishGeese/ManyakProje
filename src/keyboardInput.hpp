#pragma once

#include "input.hpp"
#include <map>

class KeyboardInput : public Input {

public:
	InputState getInputState(SDL_Keycode key) override;
	void updateInput() override;

	~KeyboardInput();
private:

	std::map<SDL_Keycode, InputState> mInputStates = std::map<SDL_Keycode, InputState>();
};