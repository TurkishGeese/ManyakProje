#pragma once

#include "input.hpp"

class AIInput : public Input {

public:
	InputState getInputState(SDL_Keycode key) override;
	InputState getInputState(InputKey key) override;
	void updateInput() override;

	~AIInput();
};