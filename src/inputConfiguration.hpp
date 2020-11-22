#pragma once

#include <map>

#include "inputKey.hpp"
#include "action.hpp"

// TODO need to have plenty of static instances of this. Figure out a system for it
class InputConfiguration {

public:
	InputConfiguration() {};

	virtual InputKey getInputKey(Action action);
	virtual ~InputConfiguration();
	
protected:
	std::map<Action, InputKey> configuration;
};