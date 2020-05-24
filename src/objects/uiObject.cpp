#include "uiObject.hpp"

#include "renderer.hpp"

UIObject::~UIObject() {
    delete mAsset;
}

void UIObject::render() {
	mAsset->render("default", mPosition, mRenderSize);
}

void UIObject::update(){}