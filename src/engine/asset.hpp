#pragma once

#include "texture.hpp"
#include "vec2.hpp"

#include <vector>
#include <string>
#include <map>

class Asset {
public:
	Asset(std::vector<Texture*> textures, std::vector<std::string> names);
	Asset(Texture* texture);
	~Asset();

	void render(std::string name, Vec2 position, Vec2 renderSize);
	bool render(std::string name, Vec2 position, Vec2 renderSize, int clip);

private:
	std::map<std::string, Texture*> mTextures;
};