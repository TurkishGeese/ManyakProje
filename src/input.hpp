#pragma once

#include "manyakSDL.hpp"

#include "inputState.hpp"
#include "inputKey.hpp"

class Input {
public:
	virtual InputState getInputState(SDL_Keycode key) = 0;
	virtual InputState getInputState(InputKey key) = 0;
	virtual void updateInput() = 0;

	virtual ~Input() {}
};
