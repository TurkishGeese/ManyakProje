#pragma once

#include "entity.hpp"

class GameState {

public:
	// This class should hold everything about the game's state in order to recreate it.
	bool initialized = false;
	Entity players[4];
};