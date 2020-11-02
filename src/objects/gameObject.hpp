#pragma once

#include "manyakSDL.hpp"
#include "asset.hpp"
#include "vec2.hpp"
#include "entity.hpp"

class GameObject {

public:
	void render();
	virtual void update(float delta) = 0;
	
	virtual ~GameObject();
protected:

	void changeActiveTexture(std::string name, int resetCount, bool force = false);

	Entity m_entity;
};