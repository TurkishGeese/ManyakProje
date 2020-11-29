#include "assetManager.hpp"

#include "manyakSDLttf.hpp"
#include "environment.hpp"

#include <iostream>
#include <fstream>

AssetManager* AssetManager::sInstance = nullptr;

std::string AssetManager::RESOURCE_DIR = "";

void AssetManager::initialize()
{
	sInstance = new AssetManager();
}

Asset* AssetManager::getAsset(std::string name)
{
	return sInstance->internalGetAsset(name);
}

Texture* AssetManager::getTexture(std::string name)
{
	return sInstance->internalGetTexture(name);
}

TextAsset* AssetManager::createText(std::string text, SDL_Color color)
{
	return sInstance->internalCreateText(text, color);
}

void AssetManager::reset()
{
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

Texture* AssetManager::internalGetTexture(std::string name) {
	auto it = mTextures.find(name);
	if (it != mTextures.end())
		return it->second;
	// TODO assert should never reach here means the texture doesn't exist
	return nullptr;
}

TextAsset* AssetManager::internalCreateText(std::string text, SDL_Color color) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(Environment::sFont, text.c_str(), color);
	if (textSurface == nullptr) {
		// TODO assert should never happen
		return nullptr;
	}
	
	TextAsset* asset = new TextAsset(new Texture(textSurface));
	mTextAssets.push_back(asset);
	SDL_FreeSurface(textSurface);
	return asset;
}

void AssetManager::internalReset() {
	for (auto element : mTextures) {
		delete element.second;
	}
	mTextures.clear();
}

void AssetManager::loadTexture(std::string name, std::string path, Vec2 clipGrid, int clips) {
	mTextures.insert({ name, new Texture(path, clipGrid, clips) });
}

void AssetManager::readAsset(std::string name) {
	std::string fileName = RESOURCE_DIR + name + ".ass";
	std::ifstream file(fileName);

	// TODO maybe refine this asset format? Maybe use json or something idk
	int entries;
	file >> entries;
	
	std::unordered_map<std::string, AssetState> states;

	for (int i = 0; i < entries; ++i) {
		std::string type;
		file >> type;
		if (type.compare("texture") == 0)
		{
			// Get the information from the file
			std::string textureName;
			std::string texturePath;
			int width;
			int height;
			file >> textureName >> texturePath >> width >> height;
			// Create the texture
			loadTexture(textureName, texturePath, { (float)width, (float)height }, width * height);
		}
		else if (type.compare("state") == 0)
		{
			// Get the information from the file
			std::string stateName;
			std::string textureName;
			int clip;
			std::vector<int> clipSet;
			file >> stateName >> textureName;
			while (true)
			{
				file >> clip;
				if (clip == -1)
					break;
				clipSet.push_back(clip);
			}
			// TODO assert clipSet.size > 0
			// Create the state
			states.insert({stateName, AssetState(textureName, clipSet)});
		}
		else
		{
			// TODO assert never should hit here
		}
	}

	file.close();

	mAssets.insert({name, new Asset(states)});
}