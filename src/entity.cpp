#include "entity.hpp"

#include "renderer.hpp"

void Entity::update(float delta) {
	switch(mAction) {
		case UP:
			mPosY -= 100.0f * delta;
			break;
		case DOWN:
			mPosY += 100.0f * delta;
			break;
		case LEFT:
			mPosX -= 100.0f * delta;
			break;
		case RIGHT:
			mPosX += 100.0f * delta;
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
	Renderer::render(texture, &renderRect, &spriteClip);
}

void Entity::input(Action action) {
	mAction = action;
}