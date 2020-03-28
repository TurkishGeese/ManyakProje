#include "entity.hpp"

void Entity::update() {

}

void Entity::attachController() {
	isPlaying = true;
}

SDL_Rect Entity:: render() {
	return { (int)mPosX, (int)mPosY, 320, 240 };
}