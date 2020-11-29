#include "inputConfiguration.hpp"

#include <assert.h>

InputKey InputConfiguration::getInputKey(Action action) {
	auto entry = configuration.find(action);
	
	if (entry == configuration.end())
		assert(entry != configuration.end() && "The action was not configured.");
	
	return entry->second;
}

InputConfiguration::~InputConfiguration() {};