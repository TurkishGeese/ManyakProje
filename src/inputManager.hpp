#pragma once

#include "manyakSDL.hpp"
#include <map>

#include "inputState.hpp"
#include "inputType.hpp"
#include "keyboardInput.hpp"
#include "aiInput.hpp"

class InputManager {

public:
	static void initialize();
	static void quit();
	static void reset();

	static void registerObject(GameObject* obj, InputType inputType);
	static void updateInput();
	static InputState getInputState(SDL_Keycode key); // This function should only be called by the level
	// TODO there should be a higher level of abstraction on objects called an Object. The below function should be able to take UIObjects as well.
	static InputState getInputState(GameObject* obj, SDL_Keycode key); // This function should only be called by objects

private:
	InputManager();

	void internalReset();

	void internalRegisterObject(GameObject* obj, InputType inputType);
	void internalUpdateInput();
	InputState internalGetInputState(SDL_Keycode key);
	InputState internalGetInputState(GameObject* obj, SDL_Keycode key);

	static InputManager* sInstance;

	KeyboardInput mKeyboard;
	AIInput mAiInput;
	std::map<GameObject*, Input*> mInputMapping = std::map<GameObject*, Input*>();
};