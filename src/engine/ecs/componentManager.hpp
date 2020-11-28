#pragma once

#include "component.hpp"
#include "entity.hpp"

#include <unordered_map>

class ComponentManager
{
public:
	virtual bool removeComponent(Entity entity) = 0;
};

template<typename T>
class ComponentManagerImpl
{
	static_assert(std::is_base_of<Component, T>::value, "T must be a component type");

public:

	T* addComponent(Entity entity);
	T* getComponent(Entity entity);
	virtual bool removeComponent(Entity entity);

private:
	std::unordered_map<Entity, T*> m_components;
};


#include <assert.h>

template<typename T>
T* ComponentManagerImpl<T>::addComponent(Entity entity)
{
	if (m_components.find(entity) != m_components.end())
		assert(false && "Tried to create a component for an entity twice? Tf are you doing.");

	T* newComponent = new T();
	m_components[entity] = newComponent;
	return newComponent;
}

template<typename T>
T* ComponentManagerImpl<T>::getComponent(Entity entity)
{
	auto res = m_components.find(entity);
	if (res == m_components.end())
		return nullptr;
	return res->second;
}

template<typename T>
bool ComponentManagerImpl<T>::removeComponent(Entity entity)
{
	auto res = m_components.find(entity);
	if (res == m_components.end())
		return false;

	delete res->second;
	m_components.erase(res);
	return true;
}