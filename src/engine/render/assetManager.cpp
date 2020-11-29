#include "assetManager.hpp"

#include <iostream>
#include <fstream>

AssetManager* AssetManager::sInstance = nullptr;

std::string AssetManager::RESOURCE_DIR = "";

void AssetManager::initialize() {
	sInstance = new AssetManager();
}

Asset* AssetManager::getAsset(std::string name) {
	return sInstance->internalGetAsset(name);
}

void AssetManager::reset() {
	sInstance->internalReset();
}


AssetManager::AssetManager() { }

Asset* AssetManager::internalGetAsset(std::string name) {
	auto it = mAssets.find(name);
	if (it != mAssets.end())
		return it->second;
	readAsset(name);
	return mAssets[name];
}

Texture* AssetManager::getTexture(std::string path, Vec2 clipGrid, int clips) {
	auto it = mTextures.find(path);
	if (it != mTextures.end())
		return it->second;
	loadTexture(path, clipGrid, clips);
	return mTextures[path];
}

void AssetManager::internalReset() {
	for (auto element : mTextures) {
		delete element.second;
	}
	mTextures.clear();
}

void AssetManager::loadTexture(std::string path, Vec2 clipGrid, int clips) {
	mTextures[path] = new Texture(path, clipGrid, clips);
}

void AssetManager::readAsset(std::string name) {
	std::string fileName = RESOURCE_DIR + name + ".ass";
	std::ifstream file(fileName);

	// TODO maybe refine this asset format? Maybe use json or something idk
	int textureCount;
	file >> textureCount;
	std::vector<std::string> names(textureCount);
	std::vector<Texture*> textures(textureCount);
	for (int i = 0; i < textureCount; ++i) {
		std::string textureName;
		std::string texturePath;
		int spriteRows;
		int spriteCols;
		int clips;
		file >> textureName >> texturePath >> spriteRows >> spriteCols >> clips;
		names[i] = textureName;
		textures[i] = getTexture(texturePath, { (float)spriteCols, (float)spriteRows }, clips);
	}

	file.close();

	mAssets[name] = new Asset(textures, names);
}