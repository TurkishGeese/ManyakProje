#pragma once

#include <map>

#include "inputKey.hpp"
#include "action.hpp"

class InputConfiguration {

public:
	InputConfiguration() {};

	virtual InputKey getInputKey(Action action);
	virtual ~InputConfiguration();
	
protected:
	std::map<Action, InputKey> configuration;
};