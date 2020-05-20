#include "uiButton.hpp"

#include "renderer.hpp"
#include "inputManager.hpp"
#include "environment.hpp"
#include "freeForAllLevel.hpp"

UIButton::UIButton(std::string idlePath, std::string activePath, float x, float y, float width, float height) {
	mPosition.x = x;
	mPosition.y = y;
	buttonWidth = width;
	buttonHeight = height;
	

	Vec2 renderSize{width, height};
	mTexture = new Texture(idlePath, renderSize);
	mTextureActive = new Texture(activePath, renderSize);

}

void UIButton::render(){
	if(isClicked){
		mTextureActive->render(mPosition);
	} else {
		mTexture->render(mPosition);
	}
}

void UIButton::update(){
	//Add changing cursor functionality when hover over button

	if(InputManager::getActionState(Action::LMB) & InputState::PRESSED) {
		if(isButtonClicked()){
			isClicked = true;
		}
	}

	if((InputManager::getActionState(Action::LMB) & InputState::RELEASED) && isClicked == true){
		if(isButtonClicked()){
			InputManager::reset();
			Environment::sChangeLevel = new FreeForAllLevel(); //Bad design put this somewhere else later
		}
		isClicked = false;
	}
}

bool UIButton::isButtonClicked(){
	Vec2 mouseLocation = InputManager::getMouseLocation();
	if((mouseLocation.x >= mPosition.x && mouseLocation.x <= mPosition.x + buttonWidth) &&
	   (mouseLocation.y >= mPosition.y && mouseLocation.y <= mPosition.y + buttonHeight)){
		   return true;
	}
	return false;
}