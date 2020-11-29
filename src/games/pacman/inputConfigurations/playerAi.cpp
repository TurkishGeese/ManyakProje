#include "playerAi.hpp"

#include "action.hpp"
#include "inputKey.hpp"
#include "logger.hpp"
#include "random.hpp"

#define MOVEMENT_CAP 5.0f

bool reset(float number) {
	if (number < 0.0f) number = number * -1;
	static const float factor = 1000.0f / MOVEMENT_CAP;
	int threshold = int(number * factor);

	int roll = Random::getRandomNumberBetween(0, 1000);
	return (roll <= threshold);
}

PlayerAi::PlayerAi() {
	isMoving = false;
	mHorizontalMovement = 0.0f;
	mVerticalMovement = 0.0f;
	mNonMovement = 0.0f;
}

InputKey PlayerAi::getInputKey(Action action) {
	float delta = 1.0f / 60.f; // TODO what was I using this for. How do I replace this

	if (isMoving) {
		bool moved = false;
		if (action == Action::WALK_RIGHT && mHorizontalMovement > 0.f) {
			mHorizontalMovement += delta;
			if (reset(mHorizontalMovement)) {
				mHorizontalMovement = 0.0f;
			}
			moved = true;
		}
		else if (action == Action::WALK_LEFT && mHorizontalMovement < 0.f) {
			mHorizontalMovement -= delta;
			if (reset(mHorizontalMovement)) {
				mHorizontalMovement = 0.0f;
			}
			moved = true;
		}
		if (action == Action::WALK_DOWN && mVerticalMovement > 0.f) {
			mVerticalMovement += delta;
			if (reset(mVerticalMovement)) {
				mVerticalMovement = 0.0f;
			}
			moved = true;
		}
		else if (action == Action::WALK_UP && mVerticalMovement < 0.f) {
			mVerticalMovement -= delta;
			if (reset(mVerticalMovement)) {
				mVerticalMovement = 0.0f;
			}
			moved = true;
		}
		if (mVerticalMovement == 0.0f && mHorizontalMovement == 0.0f) {
			isMoving = false;
		}
		if (moved)
			return KEY_LAST;
		else
			return INVALID;
	}
	else {
		mNonMovement += delta;
		if (reset(mNonMovement)) {
			mNonMovement = 0.0f;
			isMoving = true;
			if (rand() % 2 == 0) {
				mHorizontalMovement -= delta;
			}
			else {
				mHorizontalMovement += delta;
			}
			if (rand() % 2 == 0) {
				mVerticalMovement -= delta;
			}
			else {
				mVerticalMovement += delta;
			}
		}
		return INVALID;
	}
}