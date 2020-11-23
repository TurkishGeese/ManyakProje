#include "uiInputSystem.hpp"

#include "master.hpp"
#include "uiInputComponent.hpp"

void UIInputSystem::update(float delta)
{
	(void)delta;
	Master* master = Master::getInstance();
	for (auto entity : m_entities)
	{
		UIInputComponent* inputComponent = master->getComponentOfType<UIInputComponent>(entity);
		inputComponent->Update();
	}
}

void UIInputSystem::finalizeEntity(Entity entity)
{
	Master* master = Master::getInstance();
	if (master->getComponentOfType<UIInputComponent>(entity) == nullptr)
		return;

	m_entities.insert(entity);
}
