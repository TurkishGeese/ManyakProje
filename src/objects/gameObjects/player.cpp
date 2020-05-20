#include "player.hpp"

#include "renderer.hpp"
#include "inputManager.hpp"

Player::Player() {
	mDelta = 0.0f; // TODO this is needed for the AI. We should find a better way to propagate delta
					// to the AI.
	mPosition.x = 0.0f;
	mPosition.y = 0.0f;

	Vec2 renderSize{ 80.0f, 100.0f };
	SDL_Rect spriteClip = { 50, 30, 80, 100 };
	mTexture = new Texture("Idle.png", renderSize, spriteClip);
}

void Player::update(float delta) {
	mDelta = delta;
	if (InputManager::getActionState(this, Action::WALK_UP) & (InputState::PRESSED | InputState::HELD)) {
		mPosition.y -= 500.0f * delta;
	}

	if (InputManager::getActionState(this, Action::WALK_DOWN) & (InputState::PRESSED | InputState::HELD)) {
		mPosition.y += 500.0f * delta;
	}

	if (InputManager::getActionState(this, Action::WALK_LEFT) & (InputState::PRESSED | InputState::HELD)) {
		mPosition.x -= 500.0f * delta;
	}

	if (InputManager::getActionState(this, Action::WALK_RIGHT) & (InputState::PRESSED | InputState::HELD)) {
		mPosition.x += 500.0f * delta;
	}

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