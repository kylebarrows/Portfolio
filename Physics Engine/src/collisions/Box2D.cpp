#include "../../includes/collisions/Box2D.h"
#include <array>

namespace nbp
{ 
Box2D::Box2D()
	:Collider2D(colliderType::box, Vector2(0.0, 0.0)), 
	m_HalfDimensions(Vector2(0.5, 0.5))
{
	computeVertices(m_Pos, Vector2(1.0, 1.0), 0);
	computeAxes(0);
	createBoundingBox();
}

Box2D::Box2D(Vector2 pos, Vector2 half_dimensions, float angleDeg)
	:Collider2D(colliderType::box, pos), m_HalfDimensions(half_dimensions)
{
	computeVertices(pos ,Vector2(1.0, 1.0), angleDeg);
	computeAxes(angleDeg);
	createBoundingBox();
}


Vector2 Box2D::getHalfDimensions()
{
	return m_HalfDimensions;
}

void Box2D::computeVertices(Vector2 pos,Vector2 scale, float rotDeg)
{
	const float sWidth = m_HalfDimensions.x * scale.x;
	const float sHeight = m_HalfDimensions.y * scale.y;

	Vector2 pos0 = { pos.x - sWidth, pos.y + sHeight };
	Vector2 pos1 = { pos.x + sWidth, pos.y + sHeight };
	Vector2 pos2 = { pos.x + sWidth, pos.y - sHeight };
	Vector2 pos3 = { pos.x - sWidth, pos.y - sHeight };
	m_Vertices[0] = pos0.rotate(pos, rotDeg);
	m_Vertices[1] = pos1.rotate(pos, rotDeg);
	m_Vertices[2] = pos2.rotate(pos, rotDeg);
	m_Vertices[3] = pos3.rotate(pos, rotDeg);
}

void Box2D::computeAxes(float angleDeg)
{
	float angleRad = angleDeg * 3.14159265358979323846 / 180.0;
	m_Axes[0].x = std::cos(angleRad);
	m_Axes[0].y = std::sin(angleRad);
	m_Axes[1].x = -std::sin(angleRad);
	m_Axes[1].y = std::cos(angleRad);
}

void Box2D::createBoundingBox()
{
	float minX = INT_MAX;
	float minY = INT_MAX;
	float maxX = INT_MIN;
	float maxY = INT_MIN;
	for (int i = 0; i < 4; i++)
	{
		Vector2 vertex = m_Vertices[i];
		if (vertex.x < minX){ minX = vertex.x; }
		if (vertex.y < minY) { minY = vertex.y; }
		if (vertex.x > maxX) { maxX = vertex.x; }
		if (vertex.y > maxY) { maxY = vertex.y; }
	}

	m_aabb = AABB(Vector2(minX, minY), Vector2(maxX, maxY));
}

nbp::AABB Box2D::getAABB(Vector2 pos)
{
	computeVertices(pos, Vector2(1.0, 1.0), 0);
	createBoundingBox();
	return m_aabb;
}

float Box2D::computeInertia(float mass, Vector2 pos)
{
	float width = m_HalfDimensions.x * 2;
	float height = m_HalfDimensions.y * 2;
	float inertia = (1.0 / 12.0) * mass * (width * width + height * height);
	return inertia;
}

}

