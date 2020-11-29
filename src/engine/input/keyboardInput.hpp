#pragma once

#include "input.hpp"
#include <map>
#include "vec2.hpp"

class KeyboardInput : public Input {

public:
	InputState getInputState(InputKey key) override;
	void updateInput(SDL_Event& e) override;

	void preUpdateInput();
	Vec2 getMouseLocation();
	bool ctrlDown();
	bool altDown();
	bool shiftDown();

	~KeyboardInput();
private:

	std::map<InputKey, InputState> mInputStates = std::map<InputKey, InputState>();
	Vec2 mMouseLoc;
	SDL_Keymod mModState;
};