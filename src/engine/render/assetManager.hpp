#pragma once

#include "asset.hpp"
#include "texture.hpp"
#include "textAsset.hpp"

#include <string>
#include <unordered_map>
#include <vector>

class AssetManager {

public:
	static std::string RESOURCE_DIR;

	static void initialize();
	static Asset* getAsset(std::string name);
	static Texture* getTexture(std::string name);
	static TextAsset* createText(std::string text, SDL_Color color); // TODO this needs to handle multiple fonts
	static void reset(); // TODO need to be managing assets currently we don't free them (I think)

private:
	static AssetManager* sInstance;

	std::unordered_map<std::string, Texture*> mTextures;
	std::unordered_map<std::string, Asset*> mAssets;
	std::vector<TextAsset*> mTextAssets;

	AssetManager();

	Asset* internalGetAsset(std::string name);
	Texture* internalGetTexture(std::string name);
	TextAsset* internalCreateText(std::string text, SDL_Color color);
	void internalReset();
	void loadTexture(std::string name, std::string path, Vec2 clipGrid, int clips);
	void readAsset(std::string name);
};