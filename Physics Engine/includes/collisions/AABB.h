#pragma once
#include "../Vector2.h"

namespace nbp
{ 
class AABB
{
public:
	AABB();
	AABB(Vector2 minPos, Vector2 maxPos);

	Vector2 m_min;
	Vector2 m_max;
};
}