#pragma once

#include <cstdint>

// TODO In the future we will definitely need to related entities.
//	Now I'm not sure how this will effect the systems but something to keep in mind
//	When we do, we will most certainly turn this entity into
//	struct Entity
//{
//		std::uint32_t ID;
//		std::uint32_t Parent = INVALID_ENTITY;
//}
//

using Entity = std::uint32_t;
static Entity INVALID_ENTITY = -1;