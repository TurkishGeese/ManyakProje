#pragma once

#include "manyakSDL.hpp"

#include "inputState.hpp"
#include "inputKey.hpp"
#include "action.hpp"

class Input {
public:
	virtual InputState getInputState(InputKey key) = 0;
	virtual void updateInput(SDL_Event& e) = 0;

	virtual ~Input() {}
};
