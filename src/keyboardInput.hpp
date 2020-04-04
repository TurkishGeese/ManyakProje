#pragma once

#include "input.hpp"
#include <map>
#include "vec2.hpp"

class KeyboardInput : public Input {

public:
	InputState getInputState(SDL_Keycode key) override;
	InputState getInputState(InputKey key) override;
	void updateInput() override;
	Vec2 getMouseLocation();
	bool ctrlDown();
	bool altDown();
	bool shiftDown();

	~KeyboardInput();
private:

	// TODO We should move all key inputs to InputKey as well
	std::map<SDL_Keycode, InputState> mInputStates = std::map<SDL_Keycode, InputState>();
	std::map<InputKey, InputState> mMouseStates = std::map<InputKey, InputState>();
	Vec2 mMouseLoc;
	SDL_Keymod mModState;
};