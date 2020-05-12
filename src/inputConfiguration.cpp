#include "inputConfiguration.hpp"

#include <assert.h>

InputKey InputConfiguration::getInputKey(Action action) {
	auto entry = configuration.find(action);
	
	assert(entry != configuration.end() && "The action was not configured.");
	
	return entry->second;
}