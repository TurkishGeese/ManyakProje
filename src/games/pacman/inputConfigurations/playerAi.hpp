#pragma once

#include "inputConfiguration.hpp"

class Player;

class PlayerAi : public InputConfiguration {

public:
	PlayerAi();
	InputKey getInputKey(Action action) override;

private:
	bool isMoving;
	float mHorizontalMovement;
	float mVerticalMovement;
	float mNonMovement;
};