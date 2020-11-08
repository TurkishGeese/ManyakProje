#pragma once

#include <unordered_map>
#include <unordered_set>
#include "entity.hpp"
#include "system.hpp"
#include "componentManager.hpp"
#include "logger.hpp"

#include <typeinfo>

class Master
{
public:
	static Master* getInstance();

	~Master();

	// ENTITY FUNCTIONS
	Entity createEntity();

	void removeAllEntities();

	void removeEntity(Entity entity);

	void finalizeEntity(Entity entity);
	// END ENTITY FUNCTIONS

	// COMPONENT FUNCTIONS
	template<typename T>
	void registerComponentType();

	template<typename T>
	T* getComponentOfType(Entity entity);

	template<typename T>
	T* addComponentOfType(Entity entity);
	// END COMPONENT FUNCTIONS

	// SYSTEM FUNCTIONS
	template<typename T>
	T* registerSystem();

	template<typename T>
	T* getSystem();
	// END SYSTEM FUNCTIONS

	void update(float delta);
	
private:
	static Master* s_instance;

	Master();

	std::unordered_set<Entity> m_entities;
	std::unordered_map<std::string, void*> m_componentManagers;
	std::vector<System*> m_systems;
};

template<typename T>
void Master::registerComponentType()
{
	static_assert(std::is_base_of<Component, T>::value, "T must be a component type");

	const char* typeName = typeid(T).name();

	auto componentTypeManager = new ComponentManagerImpl<T>();

	m_componentManagers[typeName] = (void*)componentTypeManager;
}

template<typename T>
T* Master::getComponentOfType(Entity entity)
{
	static_assert(std::is_base_of<Component, T>::value, "T must be a component type");

	const char* typeName = typeid(T).name();

	auto it = m_componentManagers.find(typeName);
	if (it == m_componentManagers.end())
		return nullptr;

	ComponentManagerImpl<T>* mgr = (ComponentManagerImpl<T>*) it->second;
	return mgr->getComponent(entity);
}

template<typename T>
T* Master::addComponentOfType(Entity entity)
{
	static_assert(std::is_base_of<Component, T>::value, "T must be a component type");

	const char* typeName = typeid(T).name();

	auto it = m_componentManagers.find(typeName);
	if (it == m_componentManagers.end())
		return nullptr;

	ComponentManagerImpl<T>* mgr = (ComponentManagerImpl<T>*) it->second;
	return mgr->addComponent(entity);
}

template<typename T>
T* Master::registerSystem()
{
	static_assert(std::is_base_of<System, T>::value, "T must be a system type");

	T* system = new T();

	m_systems.push_back((System*)system);
	
	return system;
}

template<typename T>
T* Master::getSystem()
{
	static_assert(std::is_base_of<System, T>::value, "T must be a system type");

	for (auto system : m_systems)
	{
		if (std::string(typeid(*system).name()).compare(typeid(T).name()) == 0)
		{
			return (T*)system;
		}
	}
	return nullptr;
}
