#include "componentManager.hpp"

size_t hashEntity(const Entity& entity)
{
	return entity.Id;
}

template<typename T>
ComponentManager<T>::ComponentManager()
{
	m_components = std::unordered_map<Entity, T*, size_t(*)(const Entity&)>(0, hashEntity);
}

template<typename T>
T* ComponentManager<T>::addComponent(Entity entity, T* newComponent)
{
	if (m_components.find(entity) != m_components.end())
		return nullptr;

	m_components[entity] = newComponent;
	return newComponent;
}