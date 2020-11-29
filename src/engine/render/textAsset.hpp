#pragma once

#include "asset.hpp"

class TextAsset : public Asset {
public:
	TextAsset(Texture* texture);

	Vec2 getTextSize();
};