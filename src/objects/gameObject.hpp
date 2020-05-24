#pragma once

#include "manyakSDL.hpp"
#include "asset.hpp"
#include "vec2.hpp"

class GameObject {

public:
	void render();
	virtual void update(float delta) = 0;
	
	virtual ~GameObject();
protected:

	void changeActiveTexture(std::string name, int resetCount, bool force = false);

	Asset* mAsset;
	Vec2 mPosition;
	Vec2 mRenderSize;
	std::string mActive = "default";
	float mClip = -1.0f;
	int mClipResetCount = -1;
};