#pragma once

#include "component.hpp"
#include "asset.hpp"

struct TextureComponent : Component
{
	Asset* mAsset;
	Vec2 mRenderSize;
	std::string mActive = "default";
	float mClip = -1.0f;
	int mClipResetCount = -1;
	bool reset = false;
};