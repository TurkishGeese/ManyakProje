#include "gameObject.hpp"
#include "renderer.hpp"

void GameObject::render() {
	mTexture->render(mPosition);
}

GameObject::~GameObject() {
	delete mTexture;
}