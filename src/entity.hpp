#pragma once

#include "manyakSDL.hpp"
#include <string>

class Entity {

public:
	Entity() {};

	bool isPlaying = false;

	void update();
	void attachController();
	SDL_Rect render();

private:
	std::string mDebugName;

	float mPosX = 0.0f;
	float mPosY = 0.0f;
};