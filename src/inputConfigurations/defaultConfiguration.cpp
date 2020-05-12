#include "defaultConfiguration.hpp"

#include "action.hpp"
#include "inputKey.hpp"

DefaultConfiguration::DefaultConfiguration() {
	configuration[Action::LMB] = LEFT_CLICK;
	configuration[Action::RMB] = RIGHT_CLICK;
	configuration[Action::SELECT] = KEY_RETURN;
}