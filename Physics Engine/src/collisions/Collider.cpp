#include "../../includes/collisions/Collider.h"
#include "../../includes/RigidBody.h"

namespace nbp
{
Collider2D::Collider2D()
{
}

Collider2D::Collider2D(enum colliderType type, Vector2 pos)
	: m_Type(type), m_Pos(pos)
{
}

void Collider2D::createBoundingBox()
{
}

void Collider2D::updateBoundingBox()
{

}

float Collider2D::computeInertia(float mass, Vector2 pos)
{
	return 0.0;
}

AABB Collider2D::getAABB(Vector2 pos)
{
	return AABB();
}

Collider2D::~Collider2D()
{
}

}
