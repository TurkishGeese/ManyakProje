#include "gameObject.hpp"
#include "renderer.hpp"

#include "master.hpp"
#include "textureComponent.hpp"
#include "transformComponent.hpp"
#include "physics2DComponent.hpp"
#include "physicsSystem2D.hpp"
#include "inputComponent.hpp"
#include "input.hpp"
#include "inputConfiguration.hpp"
#include "assetManager.hpp"
#include "inputManager.hpp"

// TODO animation system plz
void changeActiveTexture(Entity entity, std::string name, int resetCount, bool force)
{
	Master* master = Master::getInstance();
	TextureComponent* textureComponent = master->getComponentOfType<TextureComponent>(entity);
	if ((textureComponent->mClipResetCount != -1 && resetCount != -1) ||
		(textureComponent->mClipResetCount == -1 && name.compare(textureComponent->mActive) != 0) || force) {
		textureComponent->mClip = 0.0f;
		textureComponent->mClipResetCount = resetCount;
		textureComponent->mActive = name;
	}
}

void playerUpdate(Entity entity, Input* input, InputConfiguration* config, float delta)
{
	Master* master = Master::getInstance();
	TextureComponent* textureComponent = master->getComponentOfType<TextureComponent>(entity);
	Physics2DComponent* physics2DComponent = master->getComponentOfType<Physics2DComponent>(entity);

	textureComponent->mClip += (delta * 6.0f);

	bool run = false;
	b2Vec2 force(0.f, 0.f);
	
	if (input->getInputState(config->getInputKey(Action::WALK_UP)) & (InputState::PRESSED | InputState::HELD)) {
		force.y -= 5000.0f;
		run = true;
	}

	if (input->getInputState(config->getInputKey(Action::WALK_DOWN)) & (InputState::PRESSED | InputState::HELD)) {
		force.y += 5000.0f;
		run = true;
	}

	if (input->getInputState(config->getInputKey(Action::WALK_LEFT)) & (InputState::PRESSED | InputState::HELD)) {
		force.x -= 5000.0f;
		run = true;
	}

	if (input->getInputState(config->getInputKey(Action::WALK_RIGHT)) & (InputState::PRESSED | InputState::HELD)) {
		force.x += 5000.0f;
		run = true;
	}
	physics2DComponent->Body->ApplyForceToCenter(force, true);

	if (run)
		changeActiveTexture(entity, "run", -1, false);
	else
		changeActiveTexture(entity, "default", -1, false);

	if (input->getInputState(config->getInputKey(Action::FIRE)) & InputState::PRESSED)
		changeActiveTexture(entity, "attack1", 1, false);
}

Entity Game::createPlayer(InputType inputType, InputConfiguration* config)
{
	Master* master = Master::getInstance();
	Entity entity = master->createEntity();
	TextureComponent* textureComponent = master->addComponentOfType<TextureComponent>(entity);
	master->addComponentOfType<TransformComponent>(entity);
	InputComponent* inputComponent = master->addComponentOfType<InputComponent>(entity);

	Physics2DComponent* physics2DComponent = master->addComponentOfType<Physics2DComponent>(entity);
	PhysicsSystem2D* physicsSystem = master->getSystem<PhysicsSystem2D>();
	physicsSystem->initializeEntityAsDynamicBody(entity, { 25.f, 50.f }, { 9.375f, 31.25f }, 1.0f, 0.9f, STATIC_ONLY);
	master->finalizeEntity(entity);

	//mDelta = 0.0f; // TODO this is needed for the AI. We should find a better way to propagate delta
					// to the AI.

	textureComponent->mRenderSize = { 120.0f, 150.0f };
	SDL_Rect spriteClip = { 50, 30, 80, 100 };
	textureComponent->mAsset = AssetManager::getAsset("player");
	textureComponent->mClip = 0.f;

	inputComponent->Config = config;
	inputComponent->InputDevice = InputManager::registerObject(inputType);
	inputComponent->Update = playerUpdate;
	return entity;
}

Entity Game::createWall(Vec2 pos, Vec2 size)
{
	Master* master = Master::getInstance();
	Entity entity = master->createEntity();
	master->addComponentOfType<TransformComponent>(entity);
	Physics2DComponent* physics2DComponent = master->addComponentOfType<Physics2DComponent>(entity);
	PhysicsSystem2D* physicsSystem = master->getSystem<PhysicsSystem2D>();
	physicsSystem->initializeEntityAsStaticBody(entity, pos, size);
	master->finalizeEntity(entity);
	return entity;
}
