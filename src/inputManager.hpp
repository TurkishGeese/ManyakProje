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
	static void reset();

	static void registerObject(GameObject* obj, InputType inputType, InputConfiguration* config);
	static void updateInput();
	static InputState getActionState(Action action);
	static InputState getActionState(GameObject* obj, Action action);

	static Vec2 getMouseLocation();
	static bool ctrlDown();
	static bool altDown();
	static bool shiftDown();

private:
	InputManager();

	void internalReset();

	void internalRegisterObject(GameObject* obj, InputType inputType, InputConfiguration* config);
	void internalUpdateInput();
	InputState internalGetActionState(Action action);
	InputState internalGetActionState(GameObject* obj, Action action);
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
	std::map<GameObject*, InputConfiguration*> mInputConfigurations = std::map<GameObject*, InputConfiguration*>();
	InputConfiguration mDefaultConfig = DefaultConfiguration();
	bool mController1Used = false;
	bool mController2Used = false;
	bool mController3Used = false;
	bool mController4Used = false;
};