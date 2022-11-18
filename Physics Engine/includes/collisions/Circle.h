#pragma once
#include "Collider.h"

namespace nbp
{ 
class Circle : public Collider2D
{
public:
	Circle();
	Circle(float radius, Vector2 pos);

	float setRadius(float radius) { m_Radius = radius; }
	float getRadius() { return m_Radius; }

	void createBoundingBox() override;
	void updateBoundingBox() override;
	AABB getAABB(Vector2 pos) override;
	float computeInertia(float mass, Vector2 pos) override;

	float m_Radius;
};
}