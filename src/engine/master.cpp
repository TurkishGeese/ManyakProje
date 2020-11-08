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
	while (m_entities.size() > 0)
	{
		removeEntity(*m_entities.begin());
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

void Master::update(float delta)
{
	// TODO These systems NEED to be ordered. Figure out a way to do it nicely
	// Maybe after all systems are initialized we should sort them or something?
	// Right now they're just in the order they're inserted in. BE CAREFUL
	for (auto system : m_systems)
	{
		system->update(delta);
	}
}
