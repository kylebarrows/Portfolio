#pragma once
#include "../Vector2.h"
#include "AABB.h"

namespace nbp
{ 
class Collider2D
{
public:
	enum class colliderType
	{
		circle,
		box
	};

	Collider2D();
	~Collider2D();
	Collider2D(enum colliderType type, Vector2 pos);

	virtual void createBoundingBox();
	virtual void updateBoundingBox();
	virtual AABB getAABB(Vector2 pos);
	colliderType getType() { return m_Type; }
	Vector2 getPosition() { return m_Pos; }
	//AABB getAABB(Vector2 pos) { return m_aabb; }
	Vector2 getMin() { return m_aabb.m_min; }
	Vector2 getMax() { return m_aabb.m_max; }

	virtual float computeInertia(float mass, Vector2 pos);

	AABB getAABB() const;
	colliderType m_Type;
	Vector2 m_Pos;

protected:
	AABB m_aabb;

};
}