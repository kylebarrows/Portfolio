#include "../includes/CollisionObject.h"

namespace nbp
{
	CollisionObject::CollisionObject()
		:m_Pos(Vector2(0.0, 0.0)), m_Scale(Vector2(1.0, 1.0)), m_Rotation(0.0)
	{

	}

	CollisionObject::CollisionObject(Vector2 pos, Vector2 scale, float rotDeg)
		:m_Pos(pos), m_Scale(scale), m_Rotation(rotDeg)
	{

	}

	CollisionObject::~CollisionObject()
	{

	}

	Vector2 CollisionObject::getPos()
	{
		return m_Pos;
	}

	void CollisionObject::setPos(Vector2 pos)
	{
		m_Pos = pos;
	}

	float CollisionObject::getRotation()
	{
		return m_Rotation;
	}
}


