#pragma once

#include "component.hpp"
#include "inputConfiguration.hpp"

class Input;

struct InputComponent : Component
{
	InputConfiguration* Config;
	Input* InputDevice;
	void (*Update)(Entity, Input*, InputConfiguration*, float);
};