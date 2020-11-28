#include "renderSystem.hpp"

#include "master.hpp"
#include "textureComponent.hpp"
#include "transformComponent.hpp"

void RenderSystem::update(float delta)
{
	(void)delta;
	Master* master = Master::getInstance();
	for (auto entity : m_entities)
	{
		TextureComponent* textureComponent = master->getComponentOfType<TextureComponent>(entity);
		TransformComponent* transformComponent = master->getComponentOfType<TransformComponent>(entity);

		if (textureComponent->mClip == -1)
			textureComponent->mAsset->render(textureComponent->mActive, transformComponent->m_transform, textureComponent->mRenderSize);
		else {
			bool reset = textureComponent->mAsset->render(textureComponent->mActive, transformComponent->m_transform, textureComponent->mRenderSize, (int)textureComponent->mClip);
			textureComponent->reset = reset;
		}
	}
}

void RenderSystem::finalizeEntity(Entity entity)
{
	Master* master = Master::getInstance();
	TextureComponent* textureComponent = master->getComponentOfType<TextureComponent>(entity);
	if (textureComponent == nullptr)
		return;
	TransformComponent* transformComponent = master->getComponentOfType<TransformComponent>(entity);
	if (transformComponent == nullptr)
		return;

	m_entities.insert(entity);
}
