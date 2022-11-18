#include "../../includes/collisions/AABB.h"
#include "../../includes/RigidBody.h"

namespace nbp
{ 
AABB::AABB()
{
}

AABB::AABB(Vector2 minPos, Vector2 maxPos)
	: m_min(minPos), m_max(maxPos)
{
}
}
