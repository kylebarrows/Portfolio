#pragma once
#include "../CollisionObject.h"
#include "../RigidBody.h"
#include "Collider.h"
#include "AABB.h"
#include "Box2D.h"
#include "Circle.h"
#include "../NMath.h"
#include "../Vector2.h"

namespace nbp
{ 
struct Contact
{
	RigidBody* rb1;
	RigidBody* rb2;
	Vector2 pos1;
	Vector2 pos2;
	float depth;
	Vector2 normal;
};

class CollisionSolver
{
public:
	bool detectCollision(CollisionObject* a, CollisionObject* b, Contact& contact);
	bool pointInAABB(Vector2 point, AABB* box, Contact& contact);
	bool pointInBox(Vector2 point, Box2D* box, Contact& contact);
	
	bool overlapAABB(AABB* aabb1, AABB* aabb2);
	bool circleVCircle(Circle* c1, Vector2 c1_pos, float r1, Circle* c2, Vector2 c2_pos, float r2, Contact& contact);
	bool boxVCircle(Circle* c1, Vector2 c1_pos, float r1, Box2D* c2, Vector2 c2_pos, float r2, Contact& contact);
	bool boxVBox(Box2D* c1, Vector2 c1_pos, float r1, Box2D* c2, Vector2 c2_pos, float r2, Contact& contact);

	//  Helpful functions
	void projectCircle(Vector2 center, float radius, Vector2 axis, float& minVal, float& maxVal);
	void projectVertices(Vector2* vertices, int nVertices, Vector2 axis, float& minVal, float& maxVal);
	int getClosestPointOnPolygon(Vector2 center, Vector2* vertices);
	float getDistanceToLine(Vector2 point, Vector2 a, Vector2 b, Vector2& contactPoint);

	void findCircleContactPoint(Vector2 centerA, float r1, Vector2 centerB, float r2, Vector2& contactPoint);
	void findCircleBoxContactPoint(Vector2 circleCenter, float radius, Vector2 boxCenter, Vector2* vertices, Vector2& contactPoint);
	void findBoxContactPoints(Vector2* verticesA, Vector2* verticesB, Vector2& contactPoint1, Vector2& contactPoint2);
};
}