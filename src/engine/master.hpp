#pragma once

#include <unordered_map>
#include <unordered_set>
#include "entity.hpp"
#include "system.hpp"
#include "componentManager.hpp"

#include <typeinfo>

class Master
{
public:
	static Master* getInstance();

	~Master();

	Entity createEntity();

	void removeAllEntities();

	template<typename T>
	void registerComponentType();

	template<typename T>
	void registerSystem();

	template<typename T>
	T* getComponentOfType(Entity entity);

	template<typename T>
	T* addComponentOfType(Entity entity);

	void removeEntity(Entity entity);

	void finalizeEntity(Entity entity);

	void update();
	
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
void Master::registerSystem()
{
	static_assert(std::is_base_of<System, T>::value, "T must be a system type");

	T* system = new T();

	m_systems.push_back((System*)system);
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
