#pragma once

#include "manyakSDL.hpp"
#include "texture.hpp"
#include "vec2.hpp"

class GameObject {

public:
	void render();
	virtual void update(float delta) = 0;
	
	virtual ~GameObject();
protected:

	Texture* mTexture;
	Vec2 mPosition;
};