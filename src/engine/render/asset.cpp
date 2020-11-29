#include "asset.hpp"

Asset::Asset(std::unordered_map<std::string, AssetState> states)
	: mStates(states)
{}

Asset::~Asset() {
}

bool Asset::render(std::string stateName, Vec2 position, Vec2 renderSize, int clip) {
	return mStates.find(stateName)->second.render(position, renderSize, clip);
}

int Asset::getClipCount(std::string stateName)
{
	return mStates.find(stateName)->second.getClipCount();
}
