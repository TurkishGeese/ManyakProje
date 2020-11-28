#pragma once

#include "input.hpp"

class AIInput : public Input {

public:
	InputState getInputState(InputKey key) override;
	void updateInput(SDL_Event& e) override;

	~AIInput();
};