#pragma once

// TODO we should really have only one option for AI and then we should be able to get the correct AI from the type itself.
// For now we can add a new AI type here for all but in the future (when we have >2 AI) we should really make it dynamic.
enum InputType {
	KEYBOARD = 0,
	AI_PLAYER = 1,
	CONTROLLER = 2
};