#include "../../includes/collisions/Circle.h"
#include "../../includes/NMath.h"

namespace nbp
{ 
Circle::Circle()
	:Collider2D(colliderType::circle, Vector2(0.0, 0.0)), m_Radius(0.5f)
{
	createBoundingBox();
}

Circle::Circle(float radius, Vector2 pos)
	: Collider2D(colliderType::circle, pos), m_Radius(radius)
{
	createBoundingBox();
}

void Circle::createBoundingBox()
{
	float minX = m_Pos.x - m_Radius;
	float minY = m_Pos.y - m_Radius;
	float maxX = m_Pos.x + m_Radius;
	float maxY = m_Pos.y + m_Radius;

	m_aabb = AABB(Vector2(minX, minY), Vector2(maxX, maxY));
}

void Circle::updateBoundingBox()
{
	m_aabb.m_min.x = m_Pos.x - m_Radius;
	m_aabb.m_min.y = m_Pos.y - m_Radius;
	m_aabb.m_max.x = m_Pos.x + m_Radius;
	m_aabb.m_max.y = m_Pos.y + m_Radius;
}

AABB Circle::getAABB(Vector2 pos)
{
	float minX = pos.x - m_Radius;
	float minY = pos.y - m_Radius;
	float maxX = pos.x + m_Radius;
	float maxY = pos.y + m_Radius;

	return AABB(Vector2(minX, minY), Vector2(maxX, maxY));
}

float Circle::computeInertia(float mass, Vector2 pos)
{
	return 0.5 * mass * m_Radius * m_Radius;
}

}
