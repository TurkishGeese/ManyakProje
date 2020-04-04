#include "player.hpp"

#include "renderer.hpp"
#include "inputManager.hpp"

// TODO BAH hate that it's in two locations. should move this to a utility class.
#if defined(MANYAK_WIN32)
    std::string resourceDirectory2 = "../../../../resources/";
#else
    std::string resourceDirectory2 = "../resources/";
#endif

Player::Player() {
    mPosX = 0.f;
    mPosY = 0.f;
    // TODO: This is player specific rects. We should move these to a Texture class and do it dynamically.
    mRenderBox = { (int)mPosX, (int)mPosY, 320, 240 };
	mSpriteClip = { 0, 0, 184, 137 };
    isClipped = true;
    mTexture = Renderer::loadTextureFromPath(resourceDirectory2 + "Idle.png");
}

void Player::update(float delta) {
	if (InputManager::getInputState(this, SDLK_UP)) {
		mPosY -= 500.0f * delta;
	}
	
	if(InputManager::getInputState(this, SDLK_DOWN)) {
		mPosY += 500.0f * delta;
	}
	
	if (InputManager::getInputState(this, SDLK_LEFT)) {
		mPosX -= 500.0f * delta;
	}
	
	if (InputManager::getInputState(this, SDLK_RIGHT)) {
		mPosX += 500.0f * delta;
	}

    mRenderBox = { (int)mPosX, (int)mPosY, 320, 240 };
}