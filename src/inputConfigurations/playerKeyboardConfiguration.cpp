#include "playerKeyboardConfiguration.hpp"

#include "action.hpp"
#include "inputKey.hpp"

PlayerKeyboardConfiguration::PlayerKeyboardConfiguration() {
	configuration[Action::WALK_UP] = KEY_w;
	configuration[Action::WALK_DOWN] = KEY_s;
	configuration[Action::WALK_LEFT] = KEY_a;
	configuration[Action::WALK_RIGHT] = KEY_d;
	configuration[Action::FIRE] = KEY_SPACE;
}