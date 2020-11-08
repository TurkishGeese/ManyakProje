#include "player.hpp"

#include "renderer.hpp"
#include "inputManager.hpp"
#include "assetManager.hpp"
#include "logger.hpp"
#include "master.hpp"
#include "textureComponent.hpp"
#include "transformComponent.hpp"
#include "physics2DComponent.hpp"
#include "physicsSystem2D.hpp"
#include "box2d/box2d.h"

Player::Player() {
	Master* master = Master::getInstance();
	m_entity = master->createEntity();
	TextureComponent* textureComponent = master->addComponentOfType<TextureComponent>(m_entity);
	master->addComponentOfType<TransformComponent>(m_entity);
	Physics2DComponent* physics2DComponent = master->addComponentOfType<Physics2DComponent>(m_entity);
	PhysicsSystem2D* physicsSystem = master->getSystem<PhysicsSystem2D>();
	physicsSystem->initializeEntityAsDynamicBody(m_entity, { 25.f, 50.f }, { 9.375f, 31.25f }, 1.0f, 0.7f, STATIC_ONLY);
	master->finalizeEntity(m_entity);

	mDelta = 0.0f; // TODO this is needed for the AI. We should find a better way to propagate delta
					// to the AI.

	textureComponent->mRenderSize = { 120.0f, 150.0f };
	SDL_Rect spriteClip = { 50, 30, 80, 100 };
	textureComponent->mAsset = AssetManager::getAsset("player");
	textureComponent->mClip = 0.f;
}

void Player::update(float delta) {
	Master* master = Master::getInstance();
	TextureComponent* textureComponent = master->getComponentOfType<TextureComponent>(m_entity);
	Physics2DComponent* physics2DComponent = master->getComponentOfType<Physics2DComponent>(m_entity);

	mDelta = delta;
	textureComponent->mClip += (delta * 6.0f);

	bool run = false;
	b2Vec2 force(0.f, 0.f);
	if (InputManager::getActionState(this, Action::WALK_UP) & (InputState::PRESSED | InputState::HELD)) {
		force.y -= 5000.0f;
		run = true;
	}

	if (InputManager::getActionState(this, Action::WALK_DOWN) & (InputState::PRESSED | InputState::HELD)) {
		force.y += 5000.0f;
		run = true;
	}

	if (InputManager::getActionState(this, Action::WALK_LEFT) & (InputState::PRESSED | InputState::HELD)) {
		force.x -= 5000.0f;
		run = true;
	}

	if (InputManager::getActionState(this, Action::WALK_RIGHT) & (InputState::PRESSED | InputState::HELD)) {
		force.x += 5000.0f;
		run = true;
	}
	physics2DComponent->Body->ApplyForceToCenter(force, true);

	if (run)
		changeActiveTexture("run", -1);
	else
		changeActiveTexture("default", -1);

	if (InputManager::getActionState(this, Action::FIRE) & InputState::PRESSED)
		changeActiveTexture("attack1", 1);
}

float Player::getLastDelta() {
	return mDelta;
}