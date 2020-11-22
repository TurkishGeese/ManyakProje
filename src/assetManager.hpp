#pragma once

#include "asset.hpp"
#include "texture.hpp"

#include <string>
#include <map>

class AssetManager {

public:
	static void initialize();
	static Asset* getAsset(std::string name);
	static void reset(); // TODO need to be managing assets currently we don't free them (I think)

private:
	static AssetManager* sInstance;
	static std::string RESOURCE_DIR;

	std::map<std::string, Texture*> mTextures;
	std::map<std::string, Asset*> mAssets;

	AssetManager();

	Asset* internalGetAsset(std::string name);
	Texture* getTexture(std::string path, Vec2 clipGrid, int clips);
	void internalReset();
	void loadTexture(std::string path, Vec2 clipGrid, int clips);
	void readAsset(std::string name);
};