#pragma once

#include "system.hpp"
#include "vec2.hpp"

#include "box2d/box2d.h"

class PhysicsSystem2D : System
{
public:
	PhysicsSystem2D();

	virtual void update(float delta);
	virtual void finalizeEntity(Entity entity);
	virtual void removeEntity(Entity entity);

	void setWorldSize(Vec2 size);
	void setWindowSize(Vec2 size);

	void initializeEntityAsStaticBody(Entity entity, Vec2 pos, Vec2 size);
	void initializeEntityAsDynamicBody(Entity entity, Vec2 pos, Vec2 size, float density, float friction);
private:

	b2Vec2 mGravity;
	b2World* mWorld;
	float mDeltaSoFar = 0.0f;
	Vec2 mWorldSize = { 0.0f, 0.0f };
	Vec2 mWindowSize = { 0.0f, 0.0f };
};