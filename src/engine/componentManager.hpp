#pragma once

#include "component.hpp"

#include <unordered_map>

template<typename T>
class ComponentManager
{
	static_assert(std::is_base_of<Component, T>::value, "T must be a component type");

public:
	ComponentManager();

	virtual T* addComponent(Entity entity) = 0;

protected:
	T* addComponent(Entity entity, T* newComponent);
	std::unordered_map<Entity, T*> m_components;
};