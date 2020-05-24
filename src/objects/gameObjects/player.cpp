#include "player.hpp"

#include "renderer.hpp"
#include "inputManager.hpp"
#include "assetManager.hpp"
#include "logger.hpp"

Player::Player() {
	mDelta = 0.0f; // TODO this is needed for the AI. We should find a better way to propagate delta
					// to the AI.
	mPosition.x = 0.0f;
	mPosition.y = 0.0f;

	//mRenderSize = { 80.0f, 100.0f };
	mRenderSize = { 120.0f, 150.0f };
	SDL_Rect spriteClip = { 50, 30, 80, 100 };
	mAsset = AssetManager::getAsset("player");
	mClip = 0.f;
}

void Player::update(float delta) {
	mDelta = delta;
	mClip += (delta * 6.0f);

	bool run = false;
	if (InputManager::getActionState(this, Action::WALK_UP) & (InputState::PRESSED | InputState::HELD)) {
		mPosition.y -= 500.0f * delta;
		run = true;
	}

	if (InputManager::getActionState(this, Action::WALK_DOWN) & (InputState::PRESSED | InputState::HELD)) {
		mPosition.y += 500.0f * delta;
		run = true;
	}

	if (InputManager::getActionState(this, Action::WALK_LEFT) & (InputState::PRESSED | InputState::HELD)) {
		mPosition.x -= 500.0f * delta;
		run = true;
	}

	if (InputManager::getActionState(this, Action::WALK_RIGHT) & (InputState::PRESSED | InputState::HELD)) {
		mPosition.x += 500.0f * delta;
		run = true;
	}

	if (run)
		changeActiveTexture("run", -1);
	else
		changeActiveTexture("default", -1);

	if (InputManager::getActionState(this, Action::FIRE) & InputState::PRESSED)
		changeActiveTexture("attack1", 1);

	// TODO TEMP boundary for niceness
	//const int SCREEN_WIDTH = 640;
	//const int SCREEN_HEIGHT = 480;
	if (mPosition.x < 0.0f) mPosition.x = 0.0f;
	if (mPosition.y < 0.0f) mPosition.y = 0.0f;
	if (mPosition.x > 560.0f) mPosition.x = 560.0f;
	if (mPosition.y > 380.0f) mPosition.y = 380.0f;
}

float Player::getLastDelta() {
	return mDelta;
}