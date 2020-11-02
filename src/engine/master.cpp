#include "master.hpp"

Master* Master::s_instance = nullptr;


Master* Master::getInstance()
{
	if (s_instance == nullptr)
		s_instance = new Master();

	return s_instance;
}

Master::Master()
{
}

Master::~Master()
{
	removeAllEntities();
	for (auto mgr : m_componentManagers)
	{
		delete mgr.second;
	}
	for (auto system : m_systems)
	{
		delete system;
	}
}

Entity Master::createEntity()
{
	static unsigned int idGen = 0;
	Entity entity = idGen++;
	m_entities.insert(entity);
	return entity;
}

void Master::removeAllEntities()
{
	for (auto entity : m_entities)
	{
		removeEntity(entity);
	}
}

void Master::removeEntity(Entity entity)
{
	for (auto mgr : m_componentManagers)
	{
		((ComponentManager*)mgr.second)->removeComponent(entity);
	}
	for (auto system : m_systems)
	{
		system->removeEntity(entity);
	}
	m_entities.erase(entity);
}

void Master::finalizeEntity(Entity entity)
{
	for (auto system : m_systems)
	{
		system->finalizeEntity(entity);
	}
}

void Master::update()
{
	for (auto system : m_systems)
	{
		system->update();
	}
}
