#pragma once

#include "texture.hpp"
#include "vec2.hpp"
#include "assetState.hpp"

#include <vector>
#include <string>
#include <unordered_map>

class Asset {
public:
	Asset(std::unordered_map<std::string, AssetState> states);
	~Asset();

	bool render(std::string stateName, Vec2 position, Vec2 renderSize, int clip);
	int getClipCount(std::string stateName);

protected:
	std::unordered_map<std::string, AssetState> mStates;
};