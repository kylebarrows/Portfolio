#pragma once
#include <iostream>
#include <vector>
#include "Vector2.h"
#include "NMath.h"
#include "collisions/CollisionSolver.h"
#include "RigidBody.h"
#include "collisions/Broadphase.h"

namespace nbp
{ 
class World
{
public:
	World();
	~World();

	RigidBody* createBody(Vector2 pos, Vector2 scale, float rotDeg,
	float restitution, float friciton);

	void registerBody(RigidBody* rb);
	void removeBody(RigidBody* rb);

	void resolveCollisionWithAngularVelocity(RigidBody* rb1, RigidBody* rb2, Contact contact);
	bool detectCollisions(float deltaTime);
	void ApplyForces();
	void moveObjects(float deltaTime);
	void step(float deltaTime);

private:
	std::vector<RigidBody*> m_RigidBodies;
	Broadphase broadphase;

	CollisionSolver solver;
};
}