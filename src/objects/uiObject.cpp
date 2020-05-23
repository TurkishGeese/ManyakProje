#include "uiObject.hpp"

#include "renderer.hpp"

UIObject::~UIObject() {
    delete mTexture;
}

void UIObject::render() {
	mTexture->render(mPosition);
}

void UIObject::update(){}