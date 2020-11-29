#include "textAsset.hpp"

TextAsset::TextAsset(Texture* texture) : Asset(std::unordered_map<std::string, AssetState>())
{
	mStates.insert({ "default", AssetState(texture, "textTexture", { 0 }) });
}

Vec2 TextAsset::getTextSize()
{
	return mStates.find("default")->second.getTexture()->getTextureSize();
}
