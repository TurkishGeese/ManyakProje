#pragma once

#include "input.hpp"
#include "inputConfiguration.hpp"
#include <map>

class ControllerInput : public Input {
public:
	InputState getInputState(InputKey key) override;
	void updateInput(SDL_Event& e) override;

	void preUpdateInput();
	void connectToController(int index);
	bool isConnected();
	SDL_JoystickID getControllerId();

	~ControllerInput();
private:
	static const int DEAD_ZONE = 8000;

	bool mConnected = false;
	SDL_GameController* mSdlController = nullptr;
	int mIndex;
	std::map<InputKey, InputState> mInputStates = std::map<InputKey, InputState>();
};