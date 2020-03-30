#pragma once

#include "manyakSDL.hpp"
#include <string>

#include "action.hpp"

class Entity {

public:
	Entity() {};

	bool isPlaying = false;

	void update(float delta);
	void attachController();
	void render(SDL_Renderer* renderer, SDL_Texture* texture);
	void input(Action action);

private:
	std::string mDebugName;

	float mPosX = 0.0f;
	float mPosY = 0.0f;

	Action mAction = NONE;
};