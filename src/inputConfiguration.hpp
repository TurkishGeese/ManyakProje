#pragma once

#include <map>

#include "inputKey.hpp"
#include "action.hpp"

class InputConfiguration {
protected:
	std::map<Action, InputKey> configuration;

public:
	InputConfiguration() {};

	InputKey getInputKey(Action action);
};