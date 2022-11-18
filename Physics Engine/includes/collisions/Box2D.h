#pragma once
#include "Collider.h"
#include <iostream>

namespace nbp
{ 
class Box2D : public Collider2D
{
public:
	Box2D();
	Box2D(Vector2 pos, Vector2 half_dimensions, float angleDeg);

	Vector2 getHalfDimensions();

	// Half length of box width and height
	Vector2 m_HalfDimensions;
	Vector2 m_Vertices[4];
	Vector2 m_Axes[2];

	void computeVertices(Vector2 pos, Vector2 scale, float angleDeg);
	void computeAxes(float angleDeg);

	void createBoundingBox() override;
	AABB getAABB(Vector2 pos) override;
	float computeInertia(float mass, Vector2 pos) override;
private:
};
}