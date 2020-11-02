#include "player.hpp"

#include "renderer.hpp"
#include "inputManager.hpp"
#include "assetManager.hpp"
#include "logger.hpp"
#include "master.hpp"
#include "textureComponent.hpp"
#include "transformComponent.hpp"

Player::Player() {
	Master* master = Master::getInstance();
	m_entity = master->createEntity();
	TextureComponent* textureComponent = master->addComponentOfType<TextureComponent>(m_entity);
	TransformComponent* transformComponent = master->addComponentOfType<TransformComponent>(m_entity);
	master->finalizeEntity(m_entity);

	mDelta = 0.0f; // TODO this is needed for the AI. We should find a better way to propagate delta
					// to the AI.
	transformComponent->m_transform.x = 0.0f;
	transformComponent->m_transform.y = 0.0f;

	//mRenderSize = { 80.0f, 100.0f };
	textureComponent->mRenderSize = { 120.0f, 150.0f };
	SDL_Rect spriteClip = { 50, 30, 80, 100 };
	textureComponent->mAsset = AssetManager::getAsset("player");
	textureComponent->mClip = 0.f;
}

void Player::update(float delta) {
	Master* master = Master::getInstance();
	TextureComponent* textureComponent = master->getComponentOfType<TextureComponent>(m_entity);
	TransformComponent* transformComponent = master->getComponentOfType<TransformComponent>(m_entity);

	mDelta = delta;
	textureComponent->mClip += (delta * 6.0f);

	bool run = false;
	if (InputManager::getActionState(this, Action::WALK_UP) & (InputState::PRESSED | InputState::HELD)) {
		transformComponent->m_transform.y -= 500.0f * delta;
		run = true;
	}

	if (InputManager::getActionState(this, Action::WALK_DOWN) & (InputState::PRESSED | InputState::HELD)) {
		transformComponent->m_transform.y += 500.0f * delta;
		run = true;
	}

	if (InputManager::getActionState(this, Action::WALK_LEFT) & (InputState::PRESSED | InputState::HELD)) {
		transformComponent->m_transform.x -= 500.0f * delta;
		run = true;
	}

	if (InputManager::getActionState(this, Action::WALK_RIGHT) & (InputState::PRESSED | InputState::HELD)) {
		transformComponent->m_transform.x += 500.0f * delta;
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
	if (transformComponent->m_transform.x < 0.0f) transformComponent->m_transform.x = 0.0f;
	if (transformComponent->m_transform.y < 0.0f) transformComponent->m_transform.y = 0.0f;
	if (transformComponent->m_transform.x > 560.0f) transformComponent->m_transform.x = 560.0f;
	if (transformComponent->m_transform.y > 380.0f) transformComponent->m_transform.y = 380.0f;
}

float Player::getLastDelta() {
	return mDelta;
}