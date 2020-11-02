#include "gameObject.hpp"
#include "renderer.hpp"

#include "master.hpp"
#include "textureComponent.hpp"
#include "transformComponent.hpp"

void GameObject::render() {
	Master* master = Master::getInstance();
	TextureComponent* textureComponent = master->getComponentOfType<TextureComponent>(m_entity);
	if (textureComponent->reset) {
		textureComponent->mClip = 0.0f;
		if (textureComponent->mClipResetCount != -1) {
			textureComponent->mClipResetCount -= 1;
			if (textureComponent->mClipResetCount == 0) {
				changeActiveTexture("default", -1, true);
			}
		}
	}
}

void GameObject::changeActiveTexture(std::string name, int resetCount, bool force) {
	Master* master = Master::getInstance();
	TextureComponent* textureComponent = master->getComponentOfType<TextureComponent>(m_entity);
	if ((textureComponent->mClipResetCount != -1 && resetCount != -1) ||
		(textureComponent->mClipResetCount == -1 && name.compare(textureComponent->mActive) != 0)|| force) {
		textureComponent->mClip = 0.0f;
		textureComponent->mClipResetCount = resetCount;
		textureComponent->mActive = name;
	}
}

GameObject::~GameObject() {
	Master* master = Master::getInstance();
	TextureComponent* textureComponent = master->getComponentOfType<TextureComponent>(m_entity);
	delete textureComponent->mAsset;
}