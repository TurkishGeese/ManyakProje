#pragma once

#include "component.hpp"
#include "inputConfiguration.hpp"

#include <functional>

class Input;

struct UIInputComponent : Component
{
	std::function<void()> Update;
	bool IsClicked = false;
};