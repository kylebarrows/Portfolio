#include "../../includes/collisions/CollisionSolver.h"
#include "../../includes/RigidBody.h"
#include <array>

namespace nbp
{ 

bool CollisionSolver::detectCollision(CollisionObject* a, CollisionObject* b, Contact& contact)
{
	return false;
}

bool CollisionSolver::pointInAABB(Vector2 point, AABB* box, Contact& contact)
{
	const Vector2 min = box->m_min;
	const Vector2 max = box->m_max;

	bool rv = point.x <= max.x && point.x >= min.x && point.y <= max.y && point.y >= min.y;
	return rv;
}

bool CollisionSolver::overlapAABB(AABB* aabb1, AABB* aabb2)
{
	Vector2 min1 = aabb1->m_min;
	Vector2 max1 = aabb1->m_max;
	Vector2 min2 = aabb2->m_min;
	Vector2 max2 = aabb2->m_max;

	return (min1.x <= max2.x && max1.x >= min2.x && min1.y <= max2.y && max1.y >= min2.y);
}

// Determines if two circles are colliding
bool CollisionSolver::circleVCircle(Circle* c1, Vector2 c1_pos, float r1, 
	Circle* c2, Vector2 c2_pos, float r2, Contact& contact)
{
	Vector2 dist = c2_pos - c1_pos;
	float distSqr = dist.x * dist.x + dist.y * dist.y;

	float radiusSum = r1 + r2;
	float radiusSumSqr = radiusSum * radiusSum;

	if (distSqr > radiusSumSqr)
	{
		return false;
	}

	Vector2 dir = dist.getNormal();

	contact.pos1 = c1_pos + dir * r1;
	contact.pos2 = contact.pos1;
	contact.normal = dir;
	contact.depth = radiusSum - dist.getLength();

	return true;
}

bool CollisionSolver::boxVCircle(Circle* c1, Vector2 c1_pos, float r1, 
	Box2D* c2, Vector2 c2_pos, float r2, Contact& contact)
{
	c2->computeVertices(c2_pos, Vector2(1, 1), r2);

	float minDepth = INT_MAX;
	float minDist = INT_MAX;

	contact.normal = Vector2(0, 0);

	Vector2 axis;
	float min1, max1, min2, max2;
	for (int i = 0; i < 4; i++)
	{
		Vector2 v1 = c2->m_Vertices[i];
		Vector2 v2 = c2->m_Vertices[(i + 1) % 4];

		Vector2 edge = v2 - v1;
		edge.normalize();
		axis = { -edge.y, edge.x };

		projectVertices(c2->m_Vertices, 4, axis, min1, max1);
		projectCircle(c1_pos, r1, axis, min2, max2);

		if (min1 >= max2 || min2 >= max1)
		{
			return false;
		}

		float depth = std::min(max2 - min1, max1 - min2);
		if (depth < minDepth)
		{
			minDepth = depth;
			contact.depth = depth;
			contact.normal = axis;
		}
	}

	// The bounding box of each object is overlapping, check the nearest point to see
	// if it is within the circle
	int index = getClosestPointOnPolygon(c1_pos, c2->m_Vertices);
	Vector2 point = c2->m_Vertices[index];

	axis = point - c1_pos;
	axis.normalize();

	projectVertices(c2->m_Vertices, 4, axis, min1, max1);
	projectCircle(c1_pos, r1, axis, min2, max2);

	if (min1 >= max2 || min2 >= max1)
	{
		return false;
	}

	float depth = std::min(max2 - min1, max1 - min2);
	if (depth < minDepth)
	{
		contact.depth = depth;
		contact.normal = axis;
	}

	// What does this do?
	if (NMath::Dot(c2_pos - c1_pos, contact.normal) < 0)
	{
		contact.normal = contact.normal * -1;
	}

	findCircleBoxContactPoint(c1_pos, r1, c2_pos, c2->m_Vertices, contact.pos1);
	contact.pos2 = contact.pos1;
	return true;
}

// Tests if 2 OBBs are intersecting using the SAT
bool CollisionSolver::boxVBox(Box2D* c1, Vector2 c1_pos ,float r1, 
	Box2D* c2, Vector2 c2_pos, float r2, Contact& contact)
{
	c1->computeVertices(c1_pos, Vector2(1, 1), r1);
	c2->computeVertices(c2_pos, Vector2(1, 1), r2);

	float minDepth = INT_MAX;
	float depth;
	Vector2 axis;
	float min1, max1, min2, max2;

	for (int i = 0; i < 4; i++)
	{
		Vector2 v1 = c1->m_Vertices[i];
		Vector2 v2 = c1->m_Vertices[(i + 1) % 4];

		Vector2 edge = v2 - v1;
		edge.normalize();
		axis = { -edge.y, edge.x };

		projectVertices(c1->m_Vertices, 4, axis, min1, max1);
		projectVertices(c2->m_Vertices, 4, axis, min2, max2);

		if (min1 >= max2 || min2 >= max1)
		{
			return false;
		}

		float depth = std::min(max2 - min1, max1 - min2);
		if (depth < minDepth)
		{
			minDepth = depth;
			contact.depth = depth;
			contact.normal = axis;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		Vector2 v1 = c2->m_Vertices[i];
		Vector2 v2 = c2->m_Vertices[(i + 1) % 4];

		Vector2 edge = v2 - v1;
		edge.normalize();
		axis = { -edge.y, edge.x };

		projectVertices(c1->m_Vertices, 4, axis, min1, max1);
		projectVertices(c2->m_Vertices, 4, axis, min2, max2);

		if (min1 >= max2 || min2 >= max1)
		{
			return false;
		}

		float depth = std::min(max2 - min1, max1 - min2);
		if (depth < minDepth)
		{
			minDepth = depth;
			contact.depth = depth;
			contact.normal = axis;
		}
	}

	if (NMath::Dot(c2_pos - c1_pos, contact.normal) < 0)
	{
		contact.normal = contact.normal * -1;
	}

	findBoxContactPoints(c1->m_Vertices, c2->m_Vertices, contact.pos1, contact.pos2);

	return true;
}

void CollisionSolver::projectCircle(Vector2 center, float radius, Vector2 axis, float& minVal, float& maxVal)
{
	Vector2 direction = axis.getNormal();
	direction = direction * radius;

	//direction = Vector2(direction.y, direction.x);

	Vector2 p1 = center + direction;
	Vector2 p2 = center - direction;

	minVal = p1.dot(axis);
	maxVal = p2.dot(axis);

	
	if (minVal > maxVal)
	{
		float temp = minVal;
		minVal = maxVal;
		maxVal = temp;
	}
}

// Projects the vertices of a polygon onto the axis, axis
// TODO: fix for polygons with n > 3 Vertices
void CollisionSolver::projectVertices(Vector2* vertices, int nVertices, Vector2 axis, float& minVal, float& maxVal)
{
	minVal = INT_MAX;
	maxVal = INT_MIN;
	for (int i = 0; i < nVertices; i++)
	{
		float p = NMath::Dot(vertices[i], axis);
		if (p < minVal)
		{
			minVal = p;
		}
		if (p > maxVal)
		{
			maxVal = p;
		}
	}
}

// Returns the index of the closest vertex to the center
int CollisionSolver::getClosestPointOnPolygon(Vector2 center, Vector2* vertices)
{
	int rv = 0;
	float dist;
	float minDist = vertices[0].distance(center);

	for (int i = 1; i < 4; i++)
	{
		dist = vertices[i].distance(center);
		if (dist < minDist)
		{
			minDist = dist;
			rv = i;
		}
	}

	return rv;
}

// Computes and returns the distance squared from point to line defined by b - a
float CollisionSolver::getDistanceToLine(Vector2 point, Vector2 a, Vector2 b, Vector2& contactPoint)
{
	Vector2 ab = b - a;

	float projection = NMath::Dot(point - a, ab);
	float lenSquared = NMath::Dot(ab, ab);
	float d = projection / lenSquared;
	if (d <= 0)
	{
		contactPoint = a;
	}
	else if (d >= 1)
	{
		contactPoint = b;
	}
	else
	{
		contactPoint = a + ab * d;
	}

	return (contactPoint - point).getLengthSquared();
}

// Calculates a single contact point between two circles,
// outputs in contactPoint variable
void CollisionSolver::findCircleContactPoint(Vector2 centerA, float r1, Vector2 centerB, float r2, Vector2& contactPoint)
{
	Vector2 dir = centerB - centerA;
	dir.normalize();

	contactPoint = centerA + dir * r1;
}

// Calculates a single contact point between a circle and a box,
// outputs in contactPoint variable
void CollisionSolver::findCircleBoxContactPoint(Vector2 circleCenter, float radius, Vector2 boxCenter, Vector2* vertices, Vector2& contactPoint)
{
	Vector2 point;
	float minDist = INT_MAX;
	float dist = 0;

	for (int i = 0; i < 4; i++)
	{
		Vector2 v1 = vertices[i];
		Vector2 v2 = vertices[(i + 1) % 4];

		dist = getDistanceToLine(circleCenter, v1, v2, point);

		if (dist < minDist)
		{
			minDist = dist;
			contactPoint = point;
		}
	}
}

// Calculates the contact points between two box colliders
void CollisionSolver::findBoxContactPoints(Vector2* verticesA, Vector2* verticesB, Vector2& contactPoint1, Vector2& contactPoint2)
{
	int numContacts;

	float minDist = INT_MAX;
	float distSq = 0;

	Vector2 contactPoint;
	contactPoint1 = Vector2(0, 0);
	contactPoint2 = Vector2(0, 0);

	for (int i = 0; i < 4; i++)
	{
		Vector2 point = verticesA[i];

		for (int j = 0; j < 4; j++)
		{
			Vector2 v1 = verticesB[j];
			Vector2 v2 = verticesB[(j + 1) % 4];

			distSq = getDistanceToLine(point, v1, v2, contactPoint);
			if (NMath::NearlyEqual(distSq, minDist))
			{
				if (!NMath::NearlyEqual(contactPoint, contactPoint1))
				{
					contactPoint2 = contactPoint;
					numContacts = 2;
				}
			}
			if (distSq < minDist)
			{
				minDist = distSq;
				numContacts = 1;
				contactPoint1 = contactPoint;
				contactPoint2 = contactPoint1;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		Vector2 point = verticesB[i];

		for (int j = 0; j < 4; j++)
		{
			Vector2 v1 = verticesA[j];
			Vector2 v2 = verticesA[(j + 1) % 4];

			distSq = getDistanceToLine(point, v1, v2, contactPoint);
			if (NMath::NearlyEqual(distSq, minDist))
			{
				if (!NMath::NearlyEqual(contactPoint, contactPoint1))
				{
					contactPoint2 = contactPoint;
					numContacts = 2;
				}
			}
			if (distSq < minDist)
			{
				minDist = distSq;
				numContacts = 1;
				contactPoint1 = contactPoint;
				contactPoint2 = contactPoint1;
			}
		}
	}
}

}
