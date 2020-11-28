#include "physicsSystem2D.hpp"

#include "master.hpp"
#include "textureComponent.hpp"
#include "transformComponent.hpp"
#include "physics2DComponent.hpp"

PhysicsSystem2D::PhysicsSystem2D() :
	mGravity(0.0f, 0.0f),
	mWorld(new b2World(mGravity))
{
}

void PhysicsSystem2D::update(float delta)
{
	mDeltaSoFar += delta;
	constexpr float simulationStep = 1.0f / 60.f;
	Master* master = Master::getInstance();
	while (mDeltaSoFar > simulationStep)
	{
		constexpr int velocityIterations = 8;
		constexpr int positionIterations = 3;
		mWorld->Step(simulationStep, velocityIterations, positionIterations);

		mDeltaSoFar -= simulationStep;
	}

	// TODO should probably decouple rendering of physical objects from the physics system
	for (auto entity : m_entities)
	{
		TransformComponent* transformComponent = master->getComponentOfType<TransformComponent>(entity);
		Physics2DComponent* physicsComponent = master->getComponentOfType<Physics2DComponent>(entity);
		const b2Transform& realTransform = physicsComponent->Body->GetTransform();
		Vec2 size = physicsComponent->size;
		transformComponent->m_transform = { (realTransform.p.x - (size.x / 2.0f)) * mWindowSize.x / mWorldSize.x, (realTransform.p.y - (size.y / 2.0f)) * mWindowSize.y / mWorldSize.y };
	}
}

void PhysicsSystem2D::finalizeEntity(Entity entity)
{
	Master* master = Master::getInstance();
	TransformComponent* transformComponent = master->getComponentOfType<TransformComponent>(entity);
	if (transformComponent == nullptr)
		return;
	Physics2DComponent* physicsComponent = master->getComponentOfType<Physics2DComponent>(entity);
	if (physicsComponent == nullptr)
		return;

	m_entities.insert(entity);
}

void PhysicsSystem2D::removeEntity(Entity entity)
{
	if (m_entities.find(entity) != m_entities.end())
	{
		Master* master = Master::getInstance();
		Physics2DComponent* component = master->getComponentOfType<Physics2DComponent>(entity);
		mWorld->DestroyBody(component->Body);
	}
	m_entities.erase(entity);
}

void PhysicsSystem2D::setWorldGravity(Vec2 g)
{
	mGravity.Set(g.x, g.y);
	mWorld->SetGravity(mGravity);
}

void PhysicsSystem2D::setWorldSize(Vec2 size)
{
	mWorldSize = size;
}

void PhysicsSystem2D::setWindowSize(Vec2 size)
{
	mWindowSize = size;
	Logger::logError("Setting window size.");
}

void PhysicsSystem2D::initializeEntityAsStaticBody(Entity entity, Vec2 pos, Vec2 size, PhysicsCategory category)
{
	Master* master = Master::getInstance();
	Physics2DComponent* component = master->getComponentOfType<Physics2DComponent>(entity);
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	component->Body = mWorld->CreateBody(&bodyDef);

	b2PolygonShape staticBox;
	staticBox.SetAsBox(size.x / 2.f, size.y / 2.f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;
	if (category == STATIC_ONLY)
	{
		fixtureDef.filter.categoryBits = STATIC_ONLY;
		fixtureDef.filter.maskBits = DEFAULT; // Collides only with default
	}

	component->Body->CreateFixture(&staticBox, 0.0f);
	component->size = size;
}

void PhysicsSystem2D::initializeEntityAsDynamicBody(Entity entity, Vec2 pos, Vec2 size, float density, float friction, PhysicsCategory category)
{
	Master* master = Master::getInstance();
	Physics2DComponent* component = master->getComponentOfType<Physics2DComponent>(entity);
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.linearDamping = 5.0f;
	component->Body = mWorld->CreateBody(&bodyDef);
	component->Body->SetFixedRotation(true); // TODO WE WILL PROLLY NEED ROTATION. Handle this better

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(size.x / 2.f, size.y / 2.f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	if (category == STATIC_ONLY)
	{
		fixtureDef.filter.categoryBits = STATIC_ONLY;
		fixtureDef.filter.maskBits = DEFAULT; // Collides only with default
	}

	component->Body->CreateFixture(&fixtureDef);
	component->size = size;
}
