#include "uiButton.hpp"

#include "renderer.hpp"
#include "inputManager.hpp"
#include "environment.hpp"
#include "freeForAllLevel.hpp"
#include "assetManager.hpp"

UIButton::UIButton(void (*func)(), std::string text, Vec2 position, Vec2 size) {
	mFunction = func;
	mPosition = position;
	mRenderSize = size;

	mAsset = AssetManager::getAsset("button");
	mText = new UIText(text, {0, 0}, { 0, 0, 0 });
	Vec2 textPosition = calculateTextPosition();
	mText->setPosition(textPosition);
}

UIButton::~UIButton(){
}

void UIButton::render(){
	if(isClicked){
		mAsset->render("active", mPosition, mRenderSize);
	} else {
		mAsset->render("default", mPosition, mRenderSize);
	}
	mText->render();
}

void UIButton::update(){
	// Add changing cursor functionality when hover over button

	if(InputManager::getActionState(Action::LMB) & InputState::PRESSED) {
		if(isButtonClicked()){
			isClicked = true;
		}
	}

	if((InputManager::getActionState(Action::LMB) & InputState::RELEASED) && isClicked == true){
		if(isButtonClicked()){
			mFunction();
		}
		isClicked = false;
	}
}

// First subtract button size from text size, then divide it into to half to calculate the optimal gap between text border and button border.
// Lastly, add the result into border position.
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

