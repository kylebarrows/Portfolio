#pragma once
#include "Vector2.h"


namespace nbp
{
class World;
class AABB;

// Collision Object stores position, rotation, and scale data
class CollisionObject
{
public:
	CollisionObject();
	CollisionObject(Vector2 pos, Vector2 scale, float rotDeg);
	~CollisionObject();

	Vector2 getPos();
	void setPos(Vector2 pos);

	float getRotation();

protected:
	Vector2 m_Pos;
	Vector2 m_Scale;
	float m_Rotation;

	friend class World;
};
}