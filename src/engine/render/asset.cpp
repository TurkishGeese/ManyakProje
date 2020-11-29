#include "asset.hpp"

Asset::Asset(std::vector<Texture*> textures, std::vector<std::string> names) {
	int textureCount = textures.size();
	mTextures = std::map<std::string, Texture*>();
	for (int i = 0; i < textureCount; ++i) {
		mTextures[names[i]] = textures[i];
	}
}

Asset::Asset(Texture* texture) {
	mTextures = std::map<std::string, Texture*>();
	mTextures["default"] = texture;
}

Asset::~Asset() {
}

void Asset::render(std::string activeTexture, Vec2 position, Vec2 renderSize) {
	mTextures[activeTexture]->render(position, renderSize);
}

bool Asset::render(std::string activeTexture, Vec2 position, Vec2 renderSize, int clip) {
	return mTextures[activeTexture]->render(position, renderSize, clip);
}
