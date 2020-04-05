#pragma once

#include "manyakSDL.hpp"
#include <map>

#include "inputState.hpp"
#include "inputType.hpp"
#include "keyboardInput.hpp"
#include "aiInput.hpp"
#include "controllerInput.hpp"
#include "gameObject.hpp"

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
	static InputState getInputState(InputKey key); // Temporary function until we move SDL_Keycodes to InputKey
	static InputState getInputState(GameObject* obj, InputKey key);

	static Vec2 getMouseLocation();
	static bool ctrlDown();
	static bool altDown();
	static bool shiftDown();

private:
	InputManager();

	void internalReset();

	void internalRegisterObject(GameObject* obj, InputType inputType);
	void internalUpdateInput();
	InputState internalGetInputState(SDL_Keycode key);
	InputState internalGetInputState(GameObject* obj, SDL_Keycode key);
	InputState internalGetInputState(InputKey key);
	InputState internalGetInputState(GameObject* obj, InputKey key);
	Vec2 internalGetMouseLocation();
	bool internalCtrlDown();
	bool internalAltDown();
	bool internalShiftDown();

	static InputManager* sInstance;

	KeyboardInput mKeyboard;
	ControllerInput mController1;
	ControllerInput mController2;
	ControllerInput mController3;
	ControllerInput mController4;
	AIInput mAiInput;
	std::map<GameObject*, Input*> mInputMapping = std::map<GameObject*, Input*>();
	bool mController1Used = false;
	bool mController2Used = false;
	bool mController3Used = false;
	bool mController4Used = false;
};