#pragma once

#include "input.hpp"

class KeyboardInput : public Input {

public:
	InputState getInputState(SDL_Keycode key) override;
	void updateInput() override;

	~KeyboardInput();
};