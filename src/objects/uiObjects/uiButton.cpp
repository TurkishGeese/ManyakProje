#include "uiButton.hpp"

#include "renderer.hpp"
#include "inputManager.hpp"
#include "environment.hpp"
#include "freeForAllLevel.hpp"

UIButton::UIButton(void (*func)(), std::string text, Vec2 position, Vec2 size) {
	function = func;
	mPosition = position;
	mRenderSize = size;

	mTexture = new Texture(idlePath, mRenderSize);
	mTextureActive = new Texture(activePath, mRenderSize);
	mText = new UIText(text, {0, 0}, { 0, 0, 0 });
	textPosition = calculateTextPosition();
	mText->setPosition(textPosition);
}

void UIButton::render(){
	if(isClicked){
		mTextureActive->render(mPosition);
	} else {
		mTexture->render(mPosition);
	}
	mText->render();
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
			function();
		}
		isClicked = false;
	}
}

Vec2 UIButton::calculateTextPosition(){
	Vec2 textSize = mText->getSize();
	return {mPosition.x + (mRenderSize.x - textSize.x) / 2, mPosition.y + (mRenderSize.y - textSize.y) / 2};
}

bool UIButton::isButtonClicked(){
	Vec2 mouseLocation = InputManager::getMouseLocation();
	if((mouseLocation.x >= mPosition.x && mouseLocation.x <= mPosition.x + mRenderSize.x) &&
	   (mouseLocation.y >= mPosition.y && mouseLocation.y <= mPosition.y + mRenderSize.y)){
		   return true;
	}
	return false;
}