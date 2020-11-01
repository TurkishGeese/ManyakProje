#include "entity.hpp"

Entity::Entity()
{
	static unsigned int idGen = 0;
	Id = idGen++;
}