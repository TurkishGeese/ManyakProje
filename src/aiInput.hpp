#pragma once

#include "input.hpp"

class AIInput : public Input {

public:
	InputState getInputState(SDL_Keycode key) override;
	void updateInput() override;

	~AIInput();
};