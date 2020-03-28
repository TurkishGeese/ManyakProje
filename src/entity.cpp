#include "entity.hpp"

void Entity::update() {
	switch(mAction) {
		case UP:
			mPosY -= 10.0f;
			break;
		case DOWN:
			mPosY += 10.0f;
			break;
		case LEFT:
			mPosX -= 10.0f;
			break;
		case RIGHT:
			mPosX += 10.0f;
			break;
		default:;
	}
	mAction = NONE;
}

void Entity::attachController() {
	isPlaying = true;
}

void Entity:: render(SDL_Renderer* renderer, SDL_Texture* texture) {
	SDL_Rect renderRect = { (int)mPosX, (int)mPosY, 320, 240 };
	SDL_Rect spriteClip = { 0, 0, 184, 137 };
    SDL_RenderCopy(renderer, texture, &spriteClip, &renderRect);
}

void Entity::input(Action action) {
	mAction = action;
}