#include "playerConfiguration.hpp"

#include "action.hpp"
#include "inputKey.hpp"

PlayerConfiguration::PlayerConfiguration() {
	configuration[Action::WALK_UP] = CONTROLLER_DPAD_UP;
	configuration[Action::WALK_DOWN] = CONTROLLER_DPAD_DOWN;
	configuration[Action::WALK_LEFT] = CONTROLLER_DPAD_LEFT;
	configuration[Action::WALK_RIGHT] = CONTROLLER_DPAD_RIGHT;
}