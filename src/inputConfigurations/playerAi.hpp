#pragma once

#include "inputConfiguration.hpp"

class Player;

class PlayerAi : public InputConfiguration {

public:
	PlayerAi(Player* player);
	InputKey getInputKey(Action action) override;

private:
	Player* mPlayer;
	bool isMoving;
	float mHorizontalMovement;
	float mVerticalMovement;
	float mNonMovement;
};