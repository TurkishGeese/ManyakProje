#include "inputSystem.hpp"

#include "master.hpp"
#include "inputComponent.hpp"

void InputSystem::update(float delta)
{
	Master* master = Master::getInstance();
	for (auto entity : m_entities)
	{
		InputComponent* inputComponent = master->getComponentOfType<InputComponent>(entity);
		inputComponent->Update(entity, inputComponent->InputDevice, inputComponent->Config, delta);
	}
}

void InputSystem::finalizeEntity(Entity entity)
{
	Master* master = Master::getInstance();
	if (master->getComponentOfType<InputComponent>(entity) == nullptr)
		return;

	m_entities.insert(entity);
}
