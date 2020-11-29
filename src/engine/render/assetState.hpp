#pragma once

#include "texture.hpp"
#include "vec2.hpp"

#include <vector>
#include <string>
#include <map>

class AssetState {
public:
	AssetState(std::string textureName, std::vector<int> clipSet);
	AssetState(Texture* texture, std::string textureName, std::vector<int> clipSet);

	bool render(Vec2 position, Vec2 renderSize, int clip);
	int getClipCount();
	Texture* getTexture();

private:
	std::string mTextureName;
	Texture* mTexture;
	std::vector<int> mClipSet;
};