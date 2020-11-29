#include "assetState.hpp"

#include "assetManager.hpp"

AssetState::AssetState(std::string textureName, std::vector<int> clipSet)
	: mTextureName(textureName), mTexture(AssetManager::getTexture(textureName)), mClipSet(clipSet)
{}

AssetState::AssetState(Texture* texture, std::string textureName, std::vector<int> clipSet)
	: mTextureName(textureName), mTexture(texture), mClipSet(clipSet)
{}


bool AssetState::render(Vec2 position, Vec2 renderSize, int clip)
{
	// TODO assert on clip >= mClipSet.size()
	(void)0;
	return mTexture->render(position, renderSize, mClipSet[0]);
}

int AssetState::getClipCount()
{
	return mClipSet.size();
}

Texture* AssetState::getTexture()
{
	return mTexture;
}
