#pragma once

#include "manyakSDL.hpp"
#include <map>

#include "inputState.hpp"
#include "inputType.hpp"
#include "keyboardInput.hpp"
#include "aiInput.hpp"
#include "controllerInput.hpp"
#include "gameObject.hpp"
#include "action.hpp"
#include "inputConfiguration.hpp"
#include "defaultConfiguration.hpp"

class InputManager {

public:
	static void initialize();
	static void quit();

	static Input* registerObject(InputType inputType);
	static void updateInput();
	static InputState getActionState(Action action);

	static Vec2 getMouseLocation();
	static bool ctrlDown();
	static bool altDown();
	static bool shiftDown();

private:
	InputManager();

	Input* internalRegisterObject(InputType inputType);
	void internalUpdateInput();
	InputState internalGetActionState(Action action);
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
	InputConfiguration mDefaultConfig = DefaultConfiguration();
	bool mController1Used = false;
	bool mController2Used = false;
	bool mController3Used = false;
	bool mController4Used = false;
};